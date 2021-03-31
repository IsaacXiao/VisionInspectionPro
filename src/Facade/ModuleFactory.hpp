#ifndef MODULE_FACTORY_HPP
#define MODULE_FACTORY_HPP

#include "CommonInclude/TypeDefine.h"
#include "CommonInclude/PlatFormHead.h"
#include <memory>
#include "CommonInclude/Memory.hpp"
#include "CommonInclude/InspectException.h"
#include "Logger/BroadCastLogger.hpp"
#include <algorithm>
#include <utility>
#include <map>

template<typename OrgT, typename PtrT, typename ModuleGroupT = EmptyClass>
class ModuleFactory
{
    typedef std::shared_ptr<DllManager> DllManagerPtr;
    typedef Dim2ArrayWrapper<char> Char2Array;
    typedef OrgT (*pCreate)( const char* name_ptr, const char* config_path );
    typedef short (*pNumber)();
    typedef void (*pNames)( char** names_ptr );
    typedef void (*pRemove)(OrgT ptr );
private:
    STRING path_;
    ModuleGroupT module_group_;
    VECTOR<STRING> names_;	
    std::map<STRING,DllManagerPtr> dll_;

    DllManagerPtr GetModuleByName( const STRING& name )
    {
        auto module_name = std::find( names_.begin(), names_.end(), name );
        if ( module_name == names_.end() )
        {
            throw CfgException( name + " does not exist in dll, config error!" );
        }
        return dll_[*module_name];  	
	}

    auto CfgLocation(DllManagerPtr dm) const 
    {
		const STRING path( dm->FileName() );
		auto no_ext_name = path.substr( 0, path.find_last_of( "." ) );
		const STRING cfg_fullname = no_ext_name + ".cfg";
		if( FileExist( cfg_fullname ) )
			return cfg_fullname;
        else
            throw CfgException( cfg_fullname + " cfg does not exist!" );
    }
public:
    ModuleFactory( const STRING& path ) : path_( path ){}

	//每个模块在创建之前先把相应的文件夹下所有全路径名DLL保存
    void Load()
    {
		names_.clear();
        dll_.clear();

        try
        {
            VECTOR<STRING> dll_full_path_name;
		    BrowseFiles( path_, "." + DllExt(), dll_full_path_name );

            for( unsigned int i = 0; i < dll_full_path_name.size(); ++i )
            {
                DllManagerPtr dm( std::make_shared<DllManager>( dll_full_path_name[i]) );
                //这个dll里有几个class	
                auto number_fn = (pNumber)dm->GetFunc( "Number" );
                short number = number_fn();
                //这几个class的名字
                auto names_fn = ( pNames )dm->GetFunc( "Names" ); 			
                Char2Array names( number, 256 );
                names_fn( names.Ptr() ); 
                
                for( int j = 0 ; j < number; ++j )
                {
                    names_.emplace_back( names[ j ] );
                    dll_.insert( std::make_pair( names[ j ], dm ) );				
                }
            }
        }
        catch(const InspectException& e) 
        {
            GlobalLogger::Record("main.exe",LOG_LEVEL::DEAD,e.what()),throw e;
        }
	}

	PtrT Create( const STRING& name )
    {
		try
		{
			DllManagerPtr dm = GetModuleByName(name);
			auto create_fn = (pCreate)dm->GetFunc("Create");

			//TODO: 按引用捕获释放资源会出问题，有空查下
			auto module_remove = [dm,name](OrgT pt)
			{
				GlobalLogger::Record("main.exe", LOG_LEVEL::TRACK, STRING("before release module: ") + name + STRING("\nin ") + __FUNCTION__);
				auto remove_fn = (pRemove)dm->GetFunc("Remove");
				remove_fn(pt);
			};
			return PtrT(create_fn(name.c_str(), CfgLocation(dm).c_str()), module_remove);
		}
		catch (const InspectException& e)
		{
			GlobalLogger::Record("main.exe", LOG_LEVEL::DEAD, STRING(e.what()) + STRING("\nin ") + __FUNCTION__), throw e;
		}
    }	
};


#endif