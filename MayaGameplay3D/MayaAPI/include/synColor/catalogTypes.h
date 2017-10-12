//
// ==================================================================
// Copyright 2014 Autodesk, Inc.  All rights reserved.
// 
// This computer source code  and related  instructions and comments are
// the unpublished confidential and proprietary information of Autodesk,
// Inc. and are  protected  under applicable  copyright and trade secret
// law. They may not  be disclosed to, copied or used by any third party
// without the prior written consent of Autodesk, Inc.
// ==================================================================
//
//! \file synColor/catalogTypes.h
//!
//! \brief List of options for managing reloading of the user transform catalog.
//!        \sa SYNCOLOR::NativeCatalogManager::reloadCatalogs.
//!

#ifndef _SYNCOLOR_CATALOG_TYPES_H
#define _SYNCOLOR_CATALOG_TYPES_H

#include <synColor/synExport.h>
#include <synColor/synColorNamespace.h>

SYN_VISIBILITY_PUSH

namespace SYNCOLOR
{
  //! \brief List of options for managing reloading of the user transform catalog.
  //!        \sa SYNCOLOR::NativeCatalogManager::reloadCatalogs.
  enum ReloadOptions
  {
    //! Update the user transform catalog only if the user transform directory
	//! has changed.
    SHARED_CATALOG_DETECT_CHANGES,
    //! Force a rebuild the user transform catalog.
    SHARED_CATALOG_FORCE_REBUILD
  };
}

SYN_VISIBILITY_POP

#endif //_SYNCOLOR_CATALOG_TYPES_H
