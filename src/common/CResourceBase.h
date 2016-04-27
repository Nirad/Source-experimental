
#pragma once
#ifndef _INC_CRESOURCEBASE_H
#define _INC_CRESOURCEBASE_H

#include "sphere_library/CSArray.h"
#include "sphere_library/CSTime.h"
#include "../game/CServerTime.h"
#include "common.h"
#include "CUID.h"
#include "CScript.h"
#include "CScriptObj.h"
#include "../game/game_enums.h"
#include "../game/game_macros.h"


class CVarDefContNum;


enum RES_TYPE	// all the script resource blocks we know how to deal with !
{
	// NOTE: SPHERE.INI, SPHERETABLE.SCP are read at start.
	// All other files are indexed from the SCPFILES directories.
	// (SI) = Single instance types.
	// (SL) = single line multiple definitions.
	// Alphabetical order.
	RES_UNKNOWN = 0,		// Not to be used.
	RES_ACCOUNT,		// Define an account instance.
	RES_ADVANCE,		// Define the advance rates for stats.
	RES_AREA,			// Complex region. (w/extra tags)
	RES_BLOCKIP,		// (SL) A list of IP's to block.
	RES_BOOK,			// A book or a page from a book.
	RES_CHARDEF,		// Define a char type. (overlap with RES_SPAWN)
	RES_COMMENT,		// A commented out block type.
	RES_DEFNAME,		// (SL) Just add a bunch of new defs and equivs str/values.
	RES_DIALOG,			// A scriptable gump dialog, text or handler block.
	RES_EVENTS,			// An Event handler block with the trigger type in it. ON=@Death etc.
	RES_FAME,
	RES_FUNCTION,		// Define a new command verb script that applies to a char.
	RES_GMPAGE,			// A GM page. (SAVED in World)
	RES_ITEMDEF,		// Define an item type. (overlap with RES_TEMPLATE)
	RES_KARMA,
	RES_KRDIALOGLIST,	// Mapping of dialog<->kr ids
	RES_MENU,			// General scriptable menus.
	RES_MOONGATES,		// (SL) Define where the moongates are.
	RES_NAMES,			// A block of possible names for a NPC type. (read as needed)
	RES_NEWBIE,			// Triggers to execute on Player creation (based on skills selected)
	RES_NOTOTITLES,		// (SI) Define the noto titles used.
	RES_OBSCENE,		// (SL) A list of obscene words.
	RES_PLEVEL,			// Define the list of commands that a PLEVEL can access. (or not access)
	RES_REGIONRESOURCE,	// Define an Ore type.
	RES_REGIONTYPE,		// Triggers etc. that can be assinged to a RES_AREA
	RES_RESOURCELIST,	// List of Sections to create lists from in DEFLIST
	RES_RESOURCES,		// (SL) list of all the resource files we should index !
	RES_ROOM,			// Non-complex region. (no extra tags)
	RES_RUNES,			// (SI) Define list of the magic runes.
	RES_SCROLL,			// SCROLL_GUEST=message scroll sent to player at guest login. SCROLL_MOTD, SCROLL_NEWBIE
	RES_SECTOR,			// Make changes to a sector. (SAVED in World)
	RES_SERVERS,		// List a number of servers in 3 line format. (Phase this out)
	RES_SKILL,			// Define attributes for a skill (how fast it raises etc)
	RES_SKILLCLASS,		// Define specifics for a char with this skill class. (ex. skill caps)
	RES_SKILLMENU,		// A menu that is attached to a skill. special arguments over other menus.
	RES_SPAWN,			// Define a list of NPC's and how often they may spawn.
	RES_SPEECH,			// A speech block with ON=*blah* in it.
	RES_SPELL,			// Define a magic spell. (0-64 are reserved)
	RES_SPHERE,			// Main Server INI block
	RES_SPHERECRYPT, // Encryption keys
	RES_STARTS,			// (SI) List of starting locations for newbies.
	RES_STAT,			// Stats elements like KARMA,STR,DEX,FOOD,FAME,CRIMINAL etc. Used for resource and desire scripts.
	RES_TELEPORTERS,	// (SL) Where are the teleporters in the world ? dungeon transports etc.
	RES_TEMPLATE,		// Define lists of items. (for filling loot etc)
	RES_TIMERF,
	RES_TIP,			// Tips (similar to RES_SCROLL) that can come up at startup.
	RES_TYPEDEF,		// Define a trigger block for a RES_WORLDITEM m_type.
	RES_TYPEDEFS,
	RES_WC,				// =WORLDCHAR
	RES_WEBPAGE,		// Define a web page template.
	RES_WI,				// =WORLDITEM
	RES_WORLDCHAR,		// Define instance of char in the world. (SAVED in World)
	RES_WORLDITEM,		// Define instance of item in the world. (SAVED in World)
	RES_WORLDLISTS,
	RES_WORLDSCRIPT,	// Something to load into a script.
	RES_WORLDVARS,
	RES_WS,				// =WORLDSCRIPT
	RES_QTY				// Don't care
};

#define RES_DIALOG_TEXT				1	// sub page for the section.
#define RES_DIALOG_BUTTON			2
#define RES_NEWBIE_MALE_DEFAULT		(10000+1)	// just an unused number for the range.
#define RES_NEWBIE_FEMALE_DEFAULT	(10000+2)
#define RES_NEWBIE_PROF_ADVANCED	(10000+3)
#define RES_NEWBIE_PROF_WARRIOR		(10000+4)
#define RES_NEWBIE_PROF_MAGE		(10000+5)
#define RES_NEWBIE_PROF_BLACKSMITH	(10000+6)
#define RES_NEWBIE_PROF_NECROMANCER	(10000+7)
#define RES_NEWBIE_PROF_PALADIN		(10000+8)
#define RES_NEWBIE_PROF_SAMURAI		(10000+9)
#define RES_NEWBIE_PROF_NINJA		(10000+10)

struct RESOURCE_ID_BASE : public CUIDBase
{
#define RES_TYPE_SHIFT	25	// leave 6 bits = 64 for RES_TYPE
#define RES_TYPE_MASK	63
#define RES_PAGE_SHIFT	18	// leave 7 bits = 128 pages of space.
#define RES_PAGE_MASK	127
#define RES_INDEX_SHIFT	0	// leave 18 bits = 262144 entries.
#define RES_INDEX_MASK	0x3FFFF
#define RES_GET_TYPE(dw)	( ( dw >> RES_TYPE_SHIFT) & RES_TYPE_MASK )
#define RES_GET_INDEX(dw)	((dw)&RES_INDEX_MASK)

public:
	RES_TYPE GetResType() const;
	int GetResIndex() const;
	int GetResPage() const;
	bool operator== ( const RESOURCE_ID_BASE & rid ) const;
};

struct RESOURCE_ID : public RESOURCE_ID_BASE
{
	RESOURCE_ID();
	RESOURCE_ID( RES_TYPE restype );
	RESOURCE_ID( RES_TYPE restype, dword index );
	RESOURCE_ID( RES_TYPE restype, dword index, int iPage );
	RESOURCE_ID_BASE & operator = ( const RESOURCE_ID_BASE & rid );
};

//*********************************************************

struct CResourceQty
{
private:
	RESOURCE_ID m_rid;	// A RES_SKILL, RES_ITEMDEF, or RES_TYPEDEF
	int64 m_iQty;			// How much of this ?
public:
	RESOURCE_ID GetResourceID() const;
	void SetResourceID( RESOURCE_ID rid, int iQty );
	RES_TYPE GetResType() const;
	int GetResIndex() const;
	int64 GetResQty() const;
	void SetResQty( int64 wQty );
	inline bool Load( lptstr & arg )
	{
		return Load( const_cast<lpctstr&>(arg) );
	}
	bool Load( lpctstr & pszCmds );
	size_t WriteKey( tchar * pszArgs, bool fQtyOnly = false, bool fKeyOnly = false ) const;
	size_t WriteNameSingle( tchar * pszArgs, int iQty = 0 ) const;
public:
	CResourceQty() : m_iQty(0) { };
};

class CResourceQtyArray : public CSTypedArray<CResourceQty, CResourceQty&>
{
	// Define a list of index id's (not references) to resource objects. (Not owned by the list)
public:
	static const char *m_sClassName;
	CResourceQtyArray();
	explicit CResourceQtyArray(lpctstr pszCmds);
	bool operator == ( const CResourceQtyArray & array ) const;
	CResourceQtyArray& operator=(const CResourceQtyArray& other);

private:
	CResourceQtyArray(const CResourceQtyArray& copy);

public:
	size_t Load( lpctstr pszCmds );
	void WriteKeys( tchar * pszArgs, size_t index = 0, bool fQtyOnly = false, bool fKeyOnly = false ) const;
	void WriteNames( tchar * pszArgs, size_t index = 0 ) const;

	size_t FindResourceID( RESOURCE_ID_BASE rid ) const;
	size_t FindResourceType( RES_TYPE type ) const;
	size_t FindResourceMatch( CObjBase * pObj ) const;
	bool IsResourceMatchAll( CChar * pChar ) const;

	inline bool ContainsResourceID( RESOURCE_ID_BASE & rid ) const
	{
		return FindResourceID(rid) != BadIndex();
	}
	inline bool ContainsResourceMatch( CObjBase * pObj ) const
	{
		return FindResourceMatch(pObj) != BadIndex();
	}

	void setNoMergeOnLoad();

private:
	bool m_mergeOnLoad;
};

//*********************************************************

class CScriptFileContext
{
	// Track a temporary context into a script.
	// NOTE: This should ONLY be stack based !
private:
	bool m_fOpenScript;	// NULL context may be legit.
	const CScript * m_pPrvScriptContext;	// previous general context before this was opened.
private:
	void Init();
public:
	static const char *m_sClassName;
	void OpenScript( const CScript * pScriptContext );
	void Close();
	CScriptFileContext();
	explicit CScriptFileContext( const CScript * pScriptContext );
	~CScriptFileContext();

private:
	CScriptFileContext(const CScriptFileContext& copy);
	CScriptFileContext& operator=(const CScriptFileContext& other);
};

class CScriptObjectContext
{
	// Track a temporary context of an object.
	// NOTE: This should ONLY be stack based !
private:
	bool m_fOpenObject;	// NULL context may be legit.
	const CScriptObj * m_pPrvObjectContext;	// previous general context before this was opened.
private:
	void Init();
public:
	static const char *m_sClassName;
	void OpenObject( const CScriptObj * pObjectContext );
	void Close();
	CScriptObjectContext();
	explicit CScriptObjectContext( const CScriptObj * pObjectContext );
	~CScriptObjectContext();

private:
	CScriptObjectContext(const CScriptObjectContext& copy);
	CScriptObjectContext& operator=(const CScriptObjectContext& other);
};

//*********************************************************

class CResourceScript : public CScript
{
	// A script file containing resource, speech, motives or events handlers.
	// NOTE: we should check periodically if this file has been altered externally ?
private:
	int		m_iOpenCount;		// How many CResourceLock(s) have this open ?
	CServerTime m_timeLastAccess;	// CWorld time of last access/Open.

	// Last time it was closed. What did the file params look like ?
	dword m_dwSize;			// Compare to see if this has changed.
	CSTime m_dateChange;	// real world time/date of last change.

private:
	void Init();
	bool CheckForChange();

public:
	static const char *m_sClassName;
	explicit CResourceScript( lpctstr pszFileName );
	CResourceScript();

private:
	CResourceScript(const CResourceScript& copy);
	CResourceScript& operator=(const CResourceScript& other);

public:
	bool IsFirstCheck() const;
	void ReSync();
	bool Open( lpctstr pszFilename = NULL, uint wFlags = OF_READ );
	virtual void Close();
	virtual void CloseForce();
};

class CResourceLock : public CScript
{
	// Open a copy of a script that is already open
	// NOTE: This should ONLY be stack based !
	// preserve the previous openers offset in the script.
private:
	CResourceScript * m_pLock;
	CScriptLineContext m_PrvLockContext;	// i must return the locked file back here.	

	CScriptFileContext m_PrvScriptContext;	// where was i before (context wise) opening this. (for error tracking)
	CScriptObjectContext m_PrvObjectContext; // object context (for error tracking)
private:
	void Init();

protected:
	virtual bool OpenBase( void * pExtra );
	virtual void CloseBase();
	virtual bool ReadTextLine( bool fRemoveBlanks );

public:
	static const char *m_sClassName;
	CResourceLock();
	~CResourceLock();

private:
	CResourceLock(const CResourceLock& copy);
	CResourceLock& operator=(const CResourceLock& other);

public:
	int OpenLock( CResourceScript * pLock, CScriptLineContext context );
	void AttachObj( const CScriptObj * pObj );
};

class CResourceDef : public CScriptObj
{
	// Define a generic  resource block in the scripts.
	// Now the scripts can be modular. resources can be defined any place.
	// NOTE: This may be loaded fully into memory or just an Index to a file.
private:
	RESOURCE_ID m_rid;		// the true resource id. (must be unique for the RES_TYPE)
protected:
	const CVarDefContNum * m_pDefName;	// The name of the resource. (optional)
public:
	static const char *m_sClassName;
	CResourceDef( RESOURCE_ID rid, lpctstr pszDefName );
	CResourceDef( RESOURCE_ID rid, const CVarDefContNum * pDefName = NULL );
	virtual ~CResourceDef();

private:
	CResourceDef(const CResourceDef& copy);
	CResourceDef& operator=(const CResourceDef& other);

public:
	RESOURCE_ID GetResourceID() const;
	RES_TYPE GetResType() const;
	int GetResPage() const;
	void CopyDef( const CResourceDef * pLink );

	// Get the name of the resource item. (Used for saving) may be number or name
	lpctstr GetResourceName() const;
	virtual lpctstr GetName() const;	// default to same as the DEFNAME name.

	// Give it another DEFNAME= even if it already has one. it's ok to have multiple names.
	bool SetResourceName( lpctstr pszName );
	void SetResourceVar( const CVarDefContNum* pVarNum );

	// unlink all this data. (tho don't delete the def as the pointer might still be used !)
	virtual void UnLink();

	bool	HasResourceName();
	bool	MakeResourceName();
};

#define MAX_TRIGGERS_ARRAY	5

class CResourceLink : public CResourceDef
{
	// A single resource object that also has part of itself remain in resource file.
	// A pre-indexed link into a script file.
	// This is a CResourceDef not fully read into memory at index time.
	// We are able to lock it and read it as needed
private:
	CResourceScript * m_pScript;	// we already found the script.
	CScriptLineContext m_Context;

	dword m_lRefInstances;	// How many CResourceRef objects refer to this ?
public:
	static const char *m_sClassName;
	dword	m_dwOnTriggers[MAX_TRIGGERS_ARRAY];

#define XTRIG_UNKNOWN 0	// bit 0 is reserved to say there are triggers here that do not conform.

public:

	void AddRefInstance();
	void DelRefInstance();
	dword GetRefInstances() const;

	bool IsLinked() const;	// been loaded from the scripts ?
	CResourceScript * GetLinkFile() const;
	size_t GetLinkOffset() const;
	void SetLink( CResourceScript * pScript );
    void CopyTransfer( CResourceLink * pLink );
	void ScanSection( RES_TYPE restype );
	void ClearTriggers();
	void SetTrigger( int i );
	bool HasTrigger( int i ) const;
	bool ResourceLock( CResourceLock & s );

public:
	CResourceLink( RESOURCE_ID rid, const CVarDefContNum * pDef = NULL );
	virtual ~CResourceLink();

private:
	CResourceLink(const CResourceLink& copy);
	CResourceLink& operator=(const CResourceLink& other);
};

class CResourceNamed : public CResourceLink
{
	// Private name pool. (does not use DEFNAME) RES_FUNCTION
public:
	static const char *m_sClassName;
	const CSString m_sName;
public:
	CResourceNamed( RESOURCE_ID rid, lpctstr pszName );
	virtual ~CResourceNamed();

private:
	CResourceNamed(const CResourceNamed& copy);
	CResourceNamed& operator=(const CResourceNamed& other);

public:
	lpctstr GetName() const;
};

//***********************************************************

class CResourceRef
{
private:
	CResourceLink* m_pLink;
public:
	static const char *m_sClassName;
	CResourceRef();
	CResourceRef( CResourceLink* pLink );
	CResourceRef(const CResourceRef& copy);
	~CResourceRef();
	CResourceRef& operator=(const CResourceRef& other);

public:
	CResourceLink* GetRef() const;
	void SetRef( CResourceLink* pLink );
	operator CResourceLink*() const;
};

class CResourceRefArray : public CSPtrTypeArray<CResourceRef>
{
	// Define a list of pointer references to resource. (Not owned by the list)
	// An indexed list of CResourceLink s.
private:
	lpctstr GetResourceName( size_t iIndex ) const;
public:
	static const char *m_sClassName;
	CResourceRefArray();
private:
	CResourceRefArray(const CResourceRefArray& copy);
	CResourceRefArray& operator=(const CResourceRefArray& other);

public:
	size_t FindResourceType( RES_TYPE type ) const;
	size_t FindResourceID( RESOURCE_ID_BASE rid ) const;
	size_t FindResourceName( RES_TYPE restype, lpctstr pszKey ) const;

	void WriteResourceRefList( CSString & sVal ) const;
	bool r_LoadVal( CScript & s, RES_TYPE restype );
	void r_Write( CScript & s, lpctstr pszKey ) const;

	inline bool ContainsResourceID( RESOURCE_ID_BASE & rid ) const
	{
		return FindResourceID(rid) != BadIndex();
	}
	inline bool ContainsResourceName( RES_TYPE restype, lpctstr & pszKey ) const
	{
		return FindResourceName(restype, pszKey) != BadIndex();
	}
};

//*********************************************************

class CResourceHashArray : public CSObjSortArray< CResourceDef*, RESOURCE_ID_BASE >
{
	// This list OWNS the CResourceDef and CResourceLink objects.
	// Sorted array of RESOURCE_ID
public:
	static const char *m_sClassName;
	CResourceHashArray();
private:
	CResourceHashArray(const CResourceHashArray& copy);
	CResourceHashArray& operator=(const CResourceHashArray& other);
public:
	int CompareKey( RESOURCE_ID_BASE rid, CResourceDef * pBase, bool fNoSpaces ) const;
};

class CResourceHash
{
public:
	static const char *m_sClassName;
	CResourceHashArray m_Array[16];
public:
	CResourceHash();
private:
	CResourceHash(const CResourceHash& copy);
	CResourceHash& operator=(const CResourceHash& other);
private:
	int GetHashArray( RESOURCE_ID_BASE rid ) const;
public:
	inline size_t BadIndex() const
	{
		return( m_Array[0].BadIndex() );
	}
	size_t FindKey( RESOURCE_ID_BASE rid ) const;
	CResourceDef* GetAt( RESOURCE_ID_BASE rid, size_t index ) const;
	size_t AddSortKey( RESOURCE_ID_BASE rid, CResourceDef* pNew );
	void SetAt( RESOURCE_ID_BASE rid, size_t index, CResourceDef* pNew );
};

//*************************************************

struct CSStringSortArray : public CSObjSortArray< tchar*, tchar* >
{
public:
	CSStringSortArray();
private:
	CSStringSortArray(const CSStringSortArray& copy);
	CSStringSortArray& operator=(const CSStringSortArray& other);
public:
	virtual void DestructElements( tchar** pElements, size_t nCount );
	// Sorted array of strings
	int CompareKey( tchar* pszID1, tchar* pszID2, bool fNoSpaces ) const;
	void AddSortString( lpctstr pszText );
};

class CObNameSortArray : public CSObjSortArray< CScriptObj*, lpctstr >
{
public:
	static const char *m_sClassName;
	CObNameSortArray();
private:
	CObNameSortArray(const CObNameSortArray& copy);
	CObNameSortArray& operator=(const CObNameSortArray& other);

public:
	// Array of CScriptObj. name sorted.
	int CompareKey( lpctstr pszID, CScriptObj* pObj, bool fNoSpaces ) const;
};

//***************************************************************8

class CResourceBase : public CScriptObj
{
protected:
	static lpctstr const sm_szResourceBlocks[RES_QTY];

	CSObjArray< CResourceScript* > m_ResourceFiles;	// All resource files we need to get blocks from later.

public:
	static const char *m_sClassName;
	CResourceHash m_ResHash;		// All script linked resources RES_QTY

	// INI File options.
	CSString m_sSCPBaseDir;		// if we want to get *.SCP files from elsewhere.

protected:
	CResourceScript * AddResourceFile( lpctstr pszName );
	void AddResourceDir( lpctstr pszDirName );

public:
	void LoadResourcesOpen( CScript * pScript );
	bool LoadResources( CResourceScript * pScript );
	static lpctstr GetResourceBlockName( RES_TYPE restype );
	lpctstr GetName() const;
	CResourceScript* GetResourceFile( size_t i );
	RESOURCE_ID ResourceGetID( RES_TYPE restype, lpctstr & pszName );
	RESOURCE_ID ResourceGetIDType( RES_TYPE restype, lpctstr pszName );
	int ResourceGetIndexType( RES_TYPE restype, lpctstr pszName );
	lpctstr ResourceGetName( RESOURCE_ID_BASE rid ) const;
	CScriptObj * ResourceGetDefByName( RES_TYPE restype, lpctstr pszName );
	bool ResourceLock( CResourceLock & s, RESOURCE_ID_BASE rid );
	bool ResourceLock( CResourceLock & s, RES_TYPE restype, lpctstr pszName );

	CResourceScript * FindResourceFile( lpctstr pszTitle );
	CResourceScript * LoadResourcesAdd( lpctstr pszNewName );
	
	virtual CResourceDef * ResourceGetDef( RESOURCE_ID_BASE rid ) const;
	virtual bool OpenResourceFind( CScript &s, lpctstr pszFilename, bool bCritical = true );
	virtual bool LoadResourceSection( CScript * pScript ) = 0;

public:
	CResourceBase() { };
	virtual ~CResourceBase() { };

private:
	CResourceBase(const CResourceBase& copy);
	CResourceBase& operator=(const CResourceBase& other);
};

inline lpctstr CResourceBase::GetResourceBlockName( RES_TYPE restype )	// static
{
	if ( restype < 0 || restype >= RES_QTY )
		restype = RES_UNKNOWN;
	return( sm_szResourceBlocks[restype] );
}

#endif // _INC_CRESOURCEBASE_H
