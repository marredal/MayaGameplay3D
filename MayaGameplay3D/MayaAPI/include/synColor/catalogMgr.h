// ==================================================================
//
// Copyright (c) 2014 Autodesk, Inc.
// All rights reserved.
//
// This computer source code and related instructions and comments are the
// unpublished confidential and proprietary information of Autodesk, Inc.
// and are protected under applicable copyright and trade secret law.
// They may not be disclosed to, copied or used by any third party without
// the prior written consent of Autodesk, Inc.
// ==================================================================
//
//!
//! \file synColor/catalogMgr.h
//!
//! \brief SynColor transform catalog manager.
//!

#ifndef _SYNCOLOR_CATALOG_MANAGER_H
#define _SYNCOLOR_CATALOG_MANAGER_H

#include <synColor/customTransformTypes.h>
#include <synColor/template.h>
#include <synColor/catalogTypes.h>


SYN_VISIBILITY_PUSH


//--------------------------------------------------------------------------------------------------
//
namespace SYNCOLOR
{
  class SynStatus;
}


//--------------------------------------------------------------------------------------------------
//
namespace SYNCOLOR
{
  //------------------------------------------------------------------------------------------------
  //! \brief SynColor transform catalog manager.
  //!
  //! The SynColor native transform catalog can be used to create native color transform
  //! templates and permits adding and removing additional transforms to the template system.
  //!
  //! The catalog manager looks at all CTF files in the Autodesk SynColor transform collection
  //! and in the shared transform directory defined in the SynColor configuration (see
  //! SYNCOLOR::getSharedColorTransformPath() ).  If metadata is present in these files, the manager
  //! determines which of the various template parameters (eg. working spaces, input color
  //! spaces and viewing transforms) the transform corresponds to.
  //!
  //! If a transform is added to the catalog manager, this transform will be available as template
  //! parameters of the corresponding type.  When a transform is added, a wrapper CTF file 
  //! containing the required metadata and referencing the added transform is added in the shared
  //! transform directory.
  //!
  //! \warning Manually removing wrapper CTF files from the shared transform directory effectively
  //!          removes the added transforms from the catalog.  Conversely adding a CTF file with the
  //!          appropriate metadata will add the associated transform to the catalog.  These changes take
  //!          effect after a restart of the client application using SynColor.
  //!
  class SYN_EXPORT NativeCatalogManager
  {
  public:
    //! \brief Get the catalog manager.
	//!
    //! \return Catalog manager singleton instance.
	//!
    static NativeCatalogManager& instance();

    //! \brief Create a native color transform template of the specified type.
    //!
    //! \param type Template type. See SYNCOLOR::TemplateType.
    //! \param pTemplate Returned template instance.
    //!
    //! \return Returns a SYNCOLOR::SynStatus. Check the error code to determine if an error occurred.
    //!
    //! \sa Detailed description of SYNCOLOR::Template.
    //!
    virtual SynStatus loadTemplate(TemplateType type, 
                                   TemplatePtr& pTemplate) = 0;

    //! \brief Refresh the catalog.
    //!
    //! This method reloads the transform catalogs.  Rebuilding of the shared transform
    //! directory catalog can be specified via the ReloadOptions.
    //!
    //! \param opt Reload action to take.  See SYNCOLOR::ReloadOptions.
    //!
    //! \return Returns a SYNCOLOR::SynStatus. Check the error code to determine if an error occurred.
    //!
    virtual SynStatus reloadCatalogs(ReloadOptions opt) = 0;

    //! \brief Callback function to obtain the list of connection color spaces.
    //!
    //! This callback is called once per available connection space.  A connection space must be
    //! specified when adding a transform to the catalog manager.
    //!
    //! \sa NativeCatalogManager::addCustomTransform().
    //!
    //! \param name Connection space name.
    //!
    typedef SynStatus (*ConnectionSpaceCallback)(const char* name);

    //! \brief Connection space list.
    //!
    //! A connection space must be specified when adding a transform to the catalog manager. With
    //! the help of the ConnectionSpaceCallback, the list of connecting spaces is made available for
    //! UI selection.
    //!
    //! \param type Transform type.  See SYNCOLOR::CustomTransformType.
    //! \param cb Callback instance.
    //!
    //! \return Returns a SYNCOLOR::SynStatus. Check the error code to determine if an error occurred.
    //!
    virtual SynStatus getConnectionSpaces(CustomTransformType type,
                                          ConnectionSpaceCallback cb) = 0;

    //! \brief Add a transform to the native catalog manager.
    //!
    //! A wrapper CTF file containing the specified metadata and referencing the added transform 
    //! is added in the shared transform directory.  This ensures that the transform remains in
    //! the catalog manager across application sessions.
    //!
    //! \warning Manually removing wrapper CTF files from the shared transform directory effectively
    //!          removes the added transforms from the catalog.  Conversely adding a CTF file with the
    //!          appropriate metadata will add the associated transform to the catalog.  These changes take
    //!          effect after a restart of the client application using SynColor.
    //!
    //! \param type Transform type.  See SYNCOLOR::CustomTransformType.
    //! \param connectionSpace Color space connecting the new transform to a known reference.  This corresponds to:
    //! 	- the transform input color space for type SYNCOLOR::CustomTransformView.
    //!		- the transform output color space for type SYNCOLOR::CustomTransformInput and SYNCOLOR::CustomTransformWorking.
    //! \param name Name of the new transform.  This name will appear in the template parameter list corresponding to the type.
    //!             This name must be unique.
    //! \param userFacingName User facing name of the new transform. This name is only meant to be displayed in the UI.
    //!             This name is not required to be unique.
    //! \param hierarchy hierarchy of the new transform.  This value will be used to organize
    //!        the transform in hierarchical groups.  NULL or empty string can be used to place
    //!        the new transform at the root of the hierarchy.
    //! \param filepath File path of the new transform.
    //!
    //! \return Returns a SYNCOLOR::SynStatus. Check the error code to determine if an error occurred.
    //!
    virtual SynStatus addCustomTransform(CustomTransformType type,
                                         const char* connectionSpace,
                                         const char* name,
                                         const char* userFacingName,
                                         const char* hierarchy,
                                         const char* filepath) = 0;

    //! \brief Remove a previously added transform from the native catalog manager.
    //!
    //! \param name Name of transform to be removed.
    //!
    //! \return Returns a SYNCOLOR::SynStatus. Check the error code to determine if an error occurred.
    virtual SynStatus removeCustomTransform(const char* name) = 0;

  protected:
    // Protected default constructor.
    NativeCatalogManager() {}

    // Protected default destructor.
    virtual ~NativeCatalogManager() {}

  private:
    //! \brief Forbidden copy constructor.
    //! \param other N/A.
    NativeCatalogManager(const NativeCatalogManager& other);
    //! \brief Forbidden assignment operator.
    //! \param other N/A.
    //! \return N/A.
    NativeCatalogManager& operator=(const NativeCatalogManager& other);
  };
};

SYN_VISIBILITY_POP

#endif // _SYNCOLOR_CATALOG_MANAGER_H
