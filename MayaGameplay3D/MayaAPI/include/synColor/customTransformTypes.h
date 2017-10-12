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
//! \file synColor/customTransformTypes.h
//!
//! \brief List of custom transform types for classifying transforms
//!        when added to the native catalog.
//!        \sa SYNCOLOR::NativeCatalogManager::addCustomTransform.
//!


#ifndef _SYNCOLOR_CUSTOM_TRANSFORM_TYPES_H
#define _SYNCOLOR_CUSTOM_TRANSFORM_TYPES_H

#include <synColor/synExport.h>
#include <synColor/synColorNamespace.h>

SYN_VISIBILITY_PUSH

namespace SYNCOLOR
{
  //! \brief List of custom transform types for classifying transforms
  //!        when added to the native catalog.
  //!        \sa SYNCOLOR::NativeCatalogManager::addCustomTransform.
  enum CustomTransformType
  {
    CustomTransformView = 0, //!< Viewing transform type.
    CustomTransformInput,    //!< Input transform type.
    CustomTransformWorking   //!< Working space transform type.
  };
}

SYN_VISIBILITY_POP

#endif //_SYNCOLOR_CUSTOM_TRANSFORM_TYPES_H
