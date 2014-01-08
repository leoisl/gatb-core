/*****************************************************************************
 *   GATB : Genome Assembly Tool Box                                         *
 *   Authors: [R.Chikhi, G.Rizk, E.Drezen]                                   *
 *   Based on Minia, Authors: [R.Chikhi, G.Rizk], CeCILL license             *
 *   Copyright (c) INRIA, CeCILL license, 2013                               *
 *****************************************************************************/

/** \file ProductHDF5.hpp
 *  \date 01/03/2013
 *  \author edrezen
 *  \brief Collection interface
 *
 *  This file holds interfaces related to the Collection interface
 */

#ifndef _GATB_CORE_TOOLS_STORAGE_IMPL_PRODUCT_HDF5_HPP_
#define _GATB_CORE_TOOLS_STORAGE_IMPL_PRODUCT_HDF5_HPP_

/********************************************************************************/

#include <gatb/tools/storage/impl/CollectionHDF5.hpp>
#include <gatb/system/impl/System.hpp>
#include <hdf5/hdf5.h>
#include <typeinfo>

/********************************************************************************/
namespace gatb      {
namespace core      {
namespace tools     {
namespace storage   {
namespace impl      {
/********************************************************************************/

class ProductHDF5Factory
{
public:

    /** */
    static Product* createProduct (const std::string& name, bool deleteIfExist, bool autoRemove)
    {
        return new ProductHDF5 (PRODUCT_HDF5, name, deleteIfExist, autoRemove);
    }

    /** */
    static Group* createGroup (ICell* parent, const std::string& name)
    {
        ProductHDF5* product = dynamic_cast<ProductHDF5*> (ICell::getRoot (parent));
        assert (product != 0);

        /** We create the instance. */
        Group* result = new Group (product->getFactory(), parent, name);

        /** We may need to create the HDF5 group. Empty name means root group, which is constructed by default. */
        if (name.empty() == false)
        {
            std::string actualName = result->getFullId('/');

            /** We create the HDF5 group if needed. */
            htri_t doesExist = H5Lexists (product->getId(), actualName.c_str(), H5P_DEFAULT);

            if (doesExist <= 0)
            {
                hid_t group = H5Gcreate (product->getId(), actualName.c_str(), H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
                H5Gclose (group);
            }
        }

        /** We return the result. */
        return result;
    }

    /** */
    template<typename Type>
    static Partition<Type>* createPartition (ICell* parent, const std::string& name, size_t nb)
    {
        ProductHDF5* product = dynamic_cast<ProductHDF5*> (ICell::getRoot (parent));
        assert (product != 0);

        std::string actualName = parent->getFullId('/') + "/" + name;

        /** We create the HDF5 group if needed. */
        htri_t doesExist = H5Lexists (product->getId(), actualName.c_str(), H5P_DEFAULT);
        if (doesExist <= 0)
        {
            hid_t group = H5Gcreate (product->getId(), actualName.c_str(), H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
            H5Gclose (group);
        }

        return new Partition<Type> (product->getFactory(), parent, name, nb);
    }

    /** */
    template<typename Type>
    static CollectionNode<Type>* createCollection (ICell* parent, const std::string& name, system::ISynchronizer* synchro)
    {
#if 1
        synchro = GlobalSynchro::singleton();
#endif

        ProductHDF5* product = dynamic_cast<ProductHDF5*> (ICell::getRoot (parent));
        assert (product != 0);

        std::string actualName = parent->getFullId('/') + "/" + name;

        return new CollectionNode<Type> (product->getFactory(), parent, name, new CollectionHDF5<Type>(product->getId(), actualName, synchro));
    }

private:

    class GlobalSynchro
    {
    public:
        static system::ISynchronizer* singleton()
        {
            static GlobalSynchro instance;
            return instance.synchro;
        }

    private:
        GlobalSynchro ()  { synchro = system::impl::System::thread().newSynchronizer(); }
        ~GlobalSynchro () { if (synchro)  { delete synchro; } }
        system::ISynchronizer* synchro;
    };

    /** */
    class ProductHDF5 : public Product
    {
    public:
        ProductHDF5 (ProductMode_e mode, const std::string& name, bool deleteIfExist, bool autoRemove)
            : Product (mode, name, autoRemove), _fileId(0), _name(name)
        {
            if (deleteIfExist)  {  system::impl::System::file().remove (getActualName());  }

            std::string usedName;

            /** We test the actual name. */
                 if (system::impl::System::file().doesExist(getActualName()))  { usedName = getActualName(); }
            else if (system::impl::System::file().doesExist(getName()))        { usedName = getName();       }

            if (usedName.empty()==false)
            {
                /** We open the existing file. */
                _fileId = H5Fopen (usedName.c_str(), H5P_DEFAULT, H5P_DEFAULT);
            }
            else
            {
                /** We create a new file using default properties. */
                _fileId = H5Fcreate (getActualName().c_str(), H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
            }
        }

        virtual ~ProductHDF5 ()
        {
            if (_autoRemove)  { remove(); }
            H5Fclose(_fileId);
        }

        hid_t getId ()  { return _fileId; }

        void remove ()
        {
            system::impl::System::file().remove (getActualName());
        }

    private:
        hid_t       _fileId;
        std::string _name;

        std::string getActualName () const  { return _name + ".h5"; }
        std::string getName       () const  { return _name;         }

    };
};

/********************************************************************************/
} } } } } /* end of namespaces. */
/********************************************************************************/

#endif /* _GATB_CORE_TOOLS_STORAGE_IMPL_PRODUCT_HDF5_HPP_ */
