// standard C++ with new header file names and std:: namespace
#include <iostream>
#include <zlib.h>
#include <cstdio>
#include "zlib/include/zlib.h"

namespace mfem {

typedef gzFile _c_file_type;

namespace gz_openmode {
enum Enum {
	//The mode parameter is as in file open :
	r = 1,
	w = 2, // to request that the gzip stream that will be written be appended to the file
	rb = 3, 	// read binary
//	wb, 		// write binary
//	//  But can also
//	wb9, 		//include a compression level
//				// or a strategy:
//	f, 			//for filtered data
//	wb6, 		// same as above
//	wb6f, 		// same as above
//	h, 			//for Huffman-only compression as in
//	wb1h, 		// same as above
//	R, 			// for run-length encoding as in
//	wb1R, 		// same as above
//	F, 			// for fixed code compression
//	wb9F, // same as above (See the description of deflateInit2 for more information about the strategy parameter.
//		  // <http://www.zlib.net/manual.html>)
//	T, // will request transparent writing or appending with no compression and not using the gzip format
//	a

	// write binary file
	wb,
	// compress  (1) best speed (6)default (9)best compression
	wb1,
	wb6,
	wb9,
	// using filtered strategy
	wb1f,
	wb6f,
	wb9f,
	// using huffman strategy
	wb1h,
	wb6h,
	wb9h,
	// using  run-length encoding strategy
	wb1R,
	wb6R,
	wb9R,
	// using  fixed strategy
	wb1F,
	wb6F,
	wb9F,
	// no compression and not using the gzip format
	wbT,
	// read binary file
};

const std::string _to_str(Enum _mode);

const Enum _to_gz_openmode(char const* val);

static size_t _count = 21;
}

typedef gz_openmode::Enum gz_openmode_type;

// ----------------------------------------------------------------------------
// Internal classes to implement gzstream. See below for user classes.
// ----------------------------------------------------------------------------

typedef gzFile _c_file_type;

class gzfilebuf: public std::streambuf {
public:
	// Types:
	typedef gzfilebuf 	_gzfilebuf_type;
protected:
	// Data Members:
	size_t 				_M_buf_size; 		// size of data buff
	_c_file_type 		_M_file;      		// file handle for compressed file
	char* 				_M_buf; 			// data buffer
	bool 				_M_opened;          // open/close state of stream
	bool 				_M_buf_allocated;  	// memory allocated for the buffer or not
	gz_openmode_type 	_M_mode;    		//

public:
	// Constructors/destructor:
	/**
	 *  @brief  Does not open any files.
	 *
	 *  The default constructor initializes the parent class using its
	 *  own default ctor.
	*/
	gzfilebuf();

	/**
	 *  @brief  The destructor closes the file first.
	*/
	virtual
	~gzfilebuf()
	{ this->close();}

	// Members:
	/**
	  *  @brief  Returns true if the external file is open.
	 */
	bool
	is_open()const throw()
	{return _M_opened;}

	_gzfilebuf_type*
	open(char const * _s, char const * _mode);

	_gzfilebuf_type*
	open(char const * _s, gz_openmode_type _mode);

	_gzfilebuf_type*
	close() throw();

protected:
	void
	_M_allocate_internal_buffer();

	void
	_M_destroy_internal_buffer() throw ();

	int
	flush_buffer();

	virtual int
	overflow(int c = traits_type::eof());

	virtual int
	underflow();

	virtual int
	sync();
};

class gzstreambase: virtual public std::ios {
public:
	typedef gzfilebuf _gzfilebuf_type;
protected:
	_gzfilebuf_type _M_gzfilebuf;
public:
	gzstreambase() {
		init(&_M_gzfilebuf);
	}
	gzstreambase(char const * name, char const *mode);
	gzstreambase(char const * name, gz_openmode_type _mode);
	~gzstreambase();
	void open(char const * name, char const *mode);
	void open(char const *name, gz_openmode_type _mode);
	void close();
	_gzfilebuf_type* rdbuf() {
		return &_M_gzfilebuf;
	}
};

// ----------------------------------------------------------------------------
// User classes. Use igzstream and ogzstream analogously to ifstream and
// ofstream respectively. They read and write files based on the gz*
// function interface of the zlib. Files are compatible with gzip compression.
// ----------------------------------------------------------------------------

class igzstream: public gzstreambase, public std::istream {
public:
	typedef gzfilebuf _gzfilebuf_type;

public:
	igzstream() :
			std::istream(&_M_gzfilebuf) {
	}
	/** Constructs a gzip compressed input stream object and opens
	 the associated file. The mode chars are as in gzopen(),
	 https://refspecs.linuxbase.org/LSB_3.0.0/LSB-PDA/LSB-PDA/zlib-gzopen-1.html.
	 Default mode is "rb". */
	igzstream(char const * name, char const *mode = "rb") :
			gzstreambase(name, gz_openmode::_to_gz_openmode(mode) ), std::istream(&_M_gzfilebuf) {
	}
	igzstream(char const * name, gz_openmode_type mode) :
				gzstreambase(name, mode), std::istream(&_M_gzfilebuf) {
		}
	_gzfilebuf_type* rdbuf() {
		return gzstreambase::rdbuf();
	}
	/** Opens a gzip compressed input stream. The mode chars are as in gzopen(),
	 https://refspecs.linuxbase.org/LSB_3.0.0/LSB-PDA/LSB-PDA/zlib-gzopen-1.html.
	 Default mode is "rb". */
	void open(char const * name, char const *mode) {
		gzstreambase::open(name, mode);
	}
	void open(char const * name, gz_openmode_type mode = gz_openmode::rb) {
			gzstreambase::open(name, mode);
		}
};

class ifgzstream: public std::istream {
public:
	/** Simple replacement for class @c std::ifstream that automatically detects
	 compressed files in gzip format and transparently uncompresses them.
	 Internally, the classes @c std::filebuf or @ref gzstreambuf are used to
	 handle the file I/O. Reading compressed files requires the MFEM
	 build-time option MFEM_USE_GZSTREAM.
	 @note For uncompressed files, the @a mode option is ignored and the file
	 is opened with @c std::ios_base::in mode.
	 @see @ref ofgzstream,
	 https://refspecs.linuxbase.org/LSB_3.0.0/LSB-PDA/LSB-PDA/zlib-gzopen-1.html. */
	ifgzstream(char const *name, char const *mode = "rb");
	ifgzstream(char const *name, gz_openmode_type mode = gz_openmode::rb);
	~ifgzstream() {
		delete buf;
	}

protected:
	std::streambuf *buf;
	static bool maybe_gz(const char *fn);
	void _init_ifgzstream(char const *name, gz_openmode_type mode);
};

class ogzstream: public gzstreambase, public std::ostream {
public:
	ogzstream() :
			std::ostream(&_M_gzfilebuf) {
	}
	/** Constructs a gzip compressed output stream object and opens
	 the associated file. The mode chars are as in gzopen(),
	 https://refspecs.linuxbase.org/LSB_3.0.0/LSB-PDA/LSB-PDA/zlib-gzopen-1.html.
	 Default mode is "wb6". */
	ogzstream(char const * name, char const *mode = "wb6f") :
			gzstreambase(name, mode), std::ostream(&_M_gzfilebuf) {
	}
	ogzstream(char const * name, gz_openmode_type const mode = gz_openmode::wb6f) :
				gzstreambase(name, mode), std::ostream(&_M_gzfilebuf) {
		}
	gzfilebuf* rdbuf() {
		return gzstreambase::rdbuf();
	}
	/** Opens a gzip compressed output stream. The mode chars are as in gzopen(),
	 https://refspecs.linuxbase.org/LSB_3.0.0/LSB-PDA/LSB-PDA/zlib-gzopen-1.html.
	 Default mode is "wb6". */
//	void open(char const * name, char const *mode) {
//		gzstreambase::open(name, mode);
//	}
	void open(char const * name, gz_openmode_type const mode = gz_openmode::wb6f) {
			gzstreambase::open(name, mode);
		}
};

class ofgzstream: public std::ostream {
public:
	static char const *default_mode; // defined in gzstream.cpp

	/** Simple replacement for class @c std::ofstream that can transparently
	 create files compressed in gzip format (when @a mode contains the
	 character @c 'z') or regular uncompressed files. Internally, the classes
	 @c std::filebuf or @ref gzstreambuf are used to handle the file I/O.
	 The mode chars are as in gzopen() with additional caveat that presence of
	 a @c 'z' character indicates desire to compress. Default mode is "zwb6".
	 Writing compressed files requires the MFEM build-time option
	 MFEM_USE_GZSTREAM.
	 @note For uncompressed files, the @a mode option is ignored and the file
	 is opened with @c std::ios_base::out mode.
	 @see @ref ifgzstream,
	 https://refspecs.linuxbase.org/LSB_3.0.0/LSB-PDA/LSB-PDA/zlib-gzopen-1.html. */
	ofgzstream(char const *name, char const *mode = default_mode);
	ofgzstream(char const *name, gz_openmode_type const mode = gz_openmode::wb6);

	~ofgzstream() {
		delete buf;
	}

protected:
	std::streambuf *buf;
};

} // namespace mfem
