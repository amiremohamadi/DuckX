/*
 * Under MIT license
 * Author: Cihan SARI (@CihanSari)
 * DuckX is a free library to work wirh docx files.
 */

#ifndef DUCKXITERATOR_H
#define DUCKXITERATOR_H

namespace pugi {
class xml_node;
}

namespace duckx {
template <class T, class P, class C = P> class Iterator {
  private:
    using ParentType = P;
    using CurrentType = C;
    ParentType parent{0};
    CurrentType current{0};
    mutable T buffer{};

  public:
    Iterator() = default;

    Iterator(ParentType parent, CurrentType current)
        : parent(parent), current(current) {}

    bool operator!=(const Iterator &other) const {
        return parent != other.parent || current != other.current;
    }

    bool operator==(const Iterator &other) const {
        return !this->operator!=(other);
    }

    Iterator &operator++() {
        this->current = this->current.next_sibling();
        return *this;
    }

    auto operator*() const -> T const & {
        // Only update the buffer when the user wants to accces to the data
        buffer.set_parent(parent);
        buffer.set_current(current);
        return buffer;
    }

    auto operator-> () const -> T const * { return &(this->operator*()); }
};

class IteratorHelper {
  private:
    using P = pugi::xml_node;
    template <class T> static auto make_begin(T const &obj) -> Iterator<T, P> {
        return Iterator<T, P>(obj.parent, obj.current);
    }

    template <class T> static auto make_end(T const &obj) -> Iterator<T, P> {
        return Iterator<T, P>(obj.parent,
                              static_cast<decltype(obj.current)>(0));
    }

    template <class T> friend auto begin(T const &) -> Iterator<T, P>;
    template <class T> friend auto end(T const &) -> Iterator<T, P>;
};

// Entry point
template <class T> auto begin(T const &obj) -> Iterator<T, pugi::xml_node> {
    return IteratorHelper::make_begin(obj);
}

template <class T> auto end(T const &obj) -> Iterator<T, pugi::xml_node> {
    return IteratorHelper::make_end(obj);
}
} // namespace duckx

#endif
