namespace factor
{

template<typename Block> struct bump_allocator {
	/* offset of 'here' and 'end' is hardcoded in compiler backends */
	cell here;
	cell start;
	cell end;
	cell size;

	explicit bump_allocator(cell size_, cell start_) :
		here(start_), start(start_), end(start_ + size_), size(size_) {}

	inline bool contains_p(Block *block)
	{
		return ((cell)block - start) < size;
	}

	inline Block *allot(cell size)
	{
		cell h = here;
		here = h + align(size,data_alignment);
		return (Block *)h;
	}
};

}