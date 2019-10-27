/*
 * Under MIT license
 * Author: Amir Mohamadi (@amiremohamadi)
 * DuckX is a free library to work wirh docx files.
 */

#ifndef DUCKXITERATOR_H
#define DUCKXITERATOR_H

namespace duckx
{
	template <class T>
	class Iterator {
	private:
		using ParentType = decltype(T::parent);
		using CurrentType = decltype(T::current);
        ParentType parent{0};
        CurrentType current{0};
		mutable T buffer{};

	public:
		Iterator() = default;

		Iterator(ParentType parent, CurrentType current) : parent(parent), current(current)
		{
		}

		bool operator!=(const Iterator& other) const
		{
			return parent != other.parent || current != other.current;
		}

		bool operator==(const Iterator& other) const
		{
			return !this->operator!=(other);
		}

		Iterator& operator++() { 
			this->current = this->current.next_sibling();
			return *this;
		}

		auto operator*() const -> T const& { 
			// Only update the buffer when the user wants to accces to the data
			buffer.set_parent(parent);
			buffer.set_current(current);
			return buffer; 
		}

		auto operator->() const -> T const* { 
			return &(this->operator*()); 
		}
	};

	class IteratorHelper {
    private:
        template <class T>
        static Iterator<T> make_begin(T const& obj) {
	        return Iterator<T>(obj.parent, obj.current);
        }

  		template <class T>
        static Iterator<T> make_end(T const& obj) {
            return Iterator<T>(obj.parent, static_cast<decltype(obj.current)>(0));
        }

        template <class T>
        friend Iterator<T> begin(T const&);
        template <class T>
        friend Iterator<T> end(T const&);
	};

	// Entry point
	template <class T>
	auto begin(T const& obj) -> Iterator<T>
	{
          return IteratorHelper::make_begin(obj);
	}

	template <class T>
	auto end(T const& obj) -> Iterator<T>
	{
          return IteratorHelper::make_end(obj);
    }
} // namespace duckx

#endif
