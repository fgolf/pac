#include <stdexcept>
#include <iostream>
#include <algorithm>

// Root includes
#include "TFile.h"
#include "TCanvas.h"

// The function definitions for the templated classes from misc_tools.h

namespace rt
{
    // help functions for the implementation
    // ---------------------------------------------------------------------------------------- //

    namespace impl
    {

        template <typename T> T& source(T &object)
        {
            return object;
        }

        template <typename T> const T& source(const T &object)
        {
            return object;
        }

        template <typename T> T& source(T *object)
        {
            return *object;
        }

        template <typename T> const T& source(const T *object)
        {
            return *object;
        }

#ifndef __RTINT__
        template <typename T> T& source(boost::shared_ptr<T> &object)
        {
            return *object;
        }

        template <typename T> const T& source(const boost::shared_ptr<T> &object)
        {
            return *object;
        }
#endif

        // test for null
        template <typename T> bool test_source(const T&) { return true; }

        template <typename T> bool test_source(const T* ptr) { return ptr != NULL; }
    }

    // function implementation
    // ---------------------------------------------------------------------------------------- //

    // get a single histgram from a root file (client is the owner)
    template <typename HistType>
    HistType* GetHistFromRootFile(const std::string& file_name, const std::string& hist_name)
    {
        std::auto_ptr<TFile> file(rt::OpenRootFile(file_name));
        HistType* hist_ptr = dynamic_cast<HistType*>(file->Get(hist_name.c_str()));
        if (!hist_ptr)
        {
            throw std::runtime_error(std::string("rt::GetHistFromRootFile() Error: '") + hist_name + "' not found.  Aborting!");
        }
        hist_ptr->SetDirectory(0);
        file->Close();
        return hist_ptr;
    }

    // print the plots to eps/png/pdf
    template <typename RootObjectType>
    void Print
    (
        RootObjectType obj,
        const std::string& file_name,
        const std::string& suffix,
        const std::string& option,
		bool logy
    )
	{
		if( !( suffix == "eps" || suffix == "png" || suffix == "pdf" ))
		{
			std::cout << "suffix " << suffix << " not valid!  No print." << std::endl;
			return;
		}

		TCanvas c1("c1_print_all_temp", "c1_print_all_temp");
		c1.SetLogy(logy);
		c1.cd();

		rt::mkdir(dirname(file_name), /*recursive=*/true);

		if (!impl::test_source(obj))
		{
			std::cout << "rt::Print() Warning: Object is NULL -- exiting!" << std::endl;
			return;
		}
		impl::source(obj).Draw( option.c_str() );
		c1.Print( (file_name + "." + suffix).c_str() );
		//rt::CopyIndexPhp(dir_name);

		return;
	}


    // print the plots to eps/png/pdf
    template <typename RootObjectType>
    void Print
    (
        std::map<std::string, RootObjectType>& m,
        const std::string& dir_name,
        const std::string& suffix,
        const std::string& option,
		bool logy
    )
    {
        if( !( suffix == "eps" || suffix == "png" || suffix == "pdf" ))
        {
            std::cout << "suffix " << suffix << " not valid!  No print." << std::endl;
            return;
        }

        TCanvas c1("c1_print_all_temp", "c1_print_all_temp");
        c1.SetLogy(logy);
        c1.cd();

        rt::mkdir(dir_name, /*recursive=*/true);

        for(typename std::map<std::string,RootObjectType>::iterator itr = m.begin(); itr != m.end(); itr++)
        {
            if (!impl::test_source(itr->second))
            {
                std::cout << "rt::Print() Warning: Object associated to " 
                    << itr->first << " is NULL -- skipping!" << std::endl;
                continue;
            }
            impl::source(itr->second).Draw( option.c_str() );
            c1.Print( (dir_name + "/" + itr->first + "." + suffix).c_str() );
        }
        rt::CopyIndexPhp(dir_name);

        return;
    }

#ifndef __CINT__

    // copy a container filtering on predicate
    template< typename InputIterator, typename OutputIterator, typename Predicate >
    OutputIterator copy_if(InputIterator first, InputIterator last, OutputIterator dest, Predicate p)
    {
        for(;first != last; ++first)
        {
            if(p(*first))
            {
                *dest = *first;
                ++dest;
            }
        }
        return dest;
    }

    // filter the container
    template<typename Container, typename Predicate>
    Container filter_container(const Container &c, Predicate p)
    {
        Container result;
        copy_if(c.begin(), c.end(), std::back_inserter(result), p);
        return result;
    }

    // combine containers 
    template <typename Container>
    Container combine_container(const Container &c1, const Container &c2)
    {
        Container result(c1);
        result.insert(c1.end(), c2.begin(), c2.end());
        return result;
    }

    // delete a pointer 
    template< typename T >
    struct delete_ptr : public std::unary_function<bool,T>
    {
       bool operator()(T* ptr) const {delete ptr; return true;}
    };

    // delete the container
    template <typename Container>
    void delete_container(const Container &c)
    {
        std::for_each(c.begin(), c.end(), delete_ptr<typename Container::value_type>());
    }

    // initialze container
    template <typename Container, typename Type>
    void init_container(Container &c, const Type& t)
    {
        std::for_each(c.begin(), c.end(), t);
    }


#endif // ifdef __CINT__

} // namespace rt
