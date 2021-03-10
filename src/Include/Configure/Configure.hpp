#ifndef CONFIGURE_HEAD_HPP
#define CONFIGURE_HEAD_HPP


#include "TinyXml/tinyxml.h"
#include "CommonInclude/TypeDefine.h"

#include <assert.h>
#include <iterator>
#include <map>
#include <type_traits>
#include <utility>
#include "CommonInclude/InspectException.h"

class XmlManager final
{
	XmlManager(const XmlManager&) = delete;
	XmlManager & operator = (const XmlManager&) = delete;
public:
	
	XmlManager( const STRING& file_name ) : file_name_( file_name )
	{			
		assert( false != doc_.LoadFile(file_name_.c_str()) );
		assert( nullptr != doc_.RootElement( ) );	
	}

	auto GetData() ->std::map<STRING,STRING>&
	{
		auto parent_nodes = GetNodes( Root(), "Properties" );
		for( unsigned int i = 0 ; i < parent_nodes.size(); ++i )
		{

			auto sub_nodes = GetNodes( parent_nodes[i], "Property" );
			for( unsigned int j = 0; j < sub_nodes.size(); ++j )
			{
				auto attr_map = GetAttributes( sub_nodes[j] );
				data_[attr_map["name"]] = attr_map["value"];
			} 
		}
		return data_;
	}
	TiXmlDocument & XmlFile( ) { return doc_; }
	void Save() { doc_.SaveFile( file_name_ ); }
private:
	inline const TiXmlNode* Root() const
	{ 
		return doc_.RootElement();
	}

	//TODO: 把下面2个函数改成全局的非成员函数
	VECTOR<TiXmlNode*> GetNodes( const TiXmlNode* parent, STRING && flag )
	{
		VECTOR<TiXmlNode*> c;
		const TiXmlNode* child{nullptr};
		for( child = parent->FirstChild(); child != NULL; child = child->NextSibling() ) 
		{
			if( ( child->Type() == TiXmlNode::ELEMENT ) && ( flag.compare( child->Value() ) == 0 ) )
			{
				std::back_inserter( c ) = const_cast<TiXmlNode*>(child);
			}
		}
		//这里的move是画蛇添足，编译器会做返回值优化
		//https://www.zhihu.com/question/57048704
		//https://blog.csdn.net/zzhongcy/article/details/86703619
		//return std::move(c);
		return c;
	}
	std::map<STRING,STRING> GetAttributes( const TiXmlNode* node ) const
	{
		assert( node != nullptr );
		const TiXmlAttribute* xml_attr = node->ToElement()->FirstAttribute();
		std::map<STRING,STRING> attr_map;
		while (xml_attr)
		{
			attr_map.insert( std::make_pair<STRING,STRING>( xml_attr->Name(), xml_attr->Value() ) );
			xml_attr = xml_attr->Next();
		}
		// Scott Meyers 说：
		// Never apply std::move or std::forward to local objects if they would otherwise be eligible for the return value optimization.
		// 翻译过来就是：请你不要老是想着帮编译器优化局部对象 因为你没有编译器聪明 不然你就试试看！！
		//return std::move(attr_map);
		return attr_map;
	}

	TiXmlDocument doc_; 
	std::string file_name_; 
	std::map<STRING,STRING> data_;
};

template<FRAMWORK_PART t, typename FacilityT = XmlManager>
class Configure
{
private:
	using DataHolder = FacilityT;
	DataHolder dataholder_;
	std::map<STRING,STRING> cfg_;
public:
	Configure( const STRING& cfg_location ):dataholder_(cfg_location){}
	~Configure(){}

	//TODO:把下面2个函数做成下标操作符可读性更好
	//用const和非const来区分读写
	std::map<STRING,STRING>& Param() &
	{
		return dataholder_.GetData();
	}

	std::map<STRING,STRING>&& Param() && 
	{
		return std::move(dataholder_.GetData()); 
	} 

	//https://www.jb51.net/article/198482.htm
	template<class VisitorPtrT, class = typename std::enable_if<std::is_pointer<VisitorPtrT>::value>::type>
	void Accept( VisitorPtrT model )
	{
		model->Visit( *this ); 
	} 
};

#endif
