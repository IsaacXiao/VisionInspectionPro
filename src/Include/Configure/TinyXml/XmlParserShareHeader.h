#if !defined XMLPARSERSHAREHEADER_H
#define  XMLPARSERSHAREHEADER_H

#ifdef XMLPARSER_EXP
#define XmlParser_Exp _declspec ( dllexport )
#else
#define XmlParser_Exp _declspec ( dllimport )
#endif

#endif