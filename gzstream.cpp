#include "gzstream.h"
#include <fstream>
#include <cstring>
#include "zlib/include/zlib.h"

namespace mfem {

namespace gz_openmode{
const std::string _to_str(gz_openmode_type _mode) {
	std::string ret;
	ret.empty();
	switch (_mode) {
	case gz_openmode::r:
		ret = "r";
		break;
	case gz_openmode::w:
		ret = "w";
		break;
	case gz_openmode::rb:
		ret = "rb";
		break;
	case gz_openmode::wb:
		ret = "wb";
		break;
	/*	case gz_openmode::wb9:
		ret = "wb9";
		break;

	case gz_openmode::f:
		ret = "f";
		break;
	case gz_openmode::wb6:
			ret = "wb6";
			break;
	case gz_openmode::wb6f:
		ret = "wb6f";
		break;
	case gz_openmode::h:
		ret = "h";
		break;
	case gz_openmode::wb1h:
		ret = "wb1h";
		break;
	case gz_openmode::R:
		ret = "R";
		break;
	case gz_openmode::wb1R:
		ret = "wb1R";
		break;
	case gz_openmode::F:
		ret = "F";
		break;
	case gz_openmode::wb9F:
		ret = "wb9F";
		break;
	case gz_openmode::T:
		ret = "T";
		break;
	case gz_openmode::a:
		ret = "a";
		break;

		// write binary file
	case gz_openmode::wb:
		ret = "r";
		break;*/
			// compress  (1) best speed (6)default (9)best compression
	case gz_openmode::wb1:
		ret = "wb1";
		break;
	case gz_openmode::wb6:
		ret = "wb6";
		break;
	case gz_openmode::wb9:
		ret = "wb9";
		break;
			// using filtered strategy
	case gz_openmode::wb1f:
		ret = "wb1f";
		break;
	case gz_openmode::wb6f:
		ret = "wb6f";
		break;
	case gz_openmode::wb9f:
		ret = "wb9f";
		break;
			// using huffman strategy
	case gz_openmode::wb1h:
		ret = "wb1h";
		break;
	case gz_openmode::wb6h:
		ret = "wb6h";
		break;
	case gz_openmode::wb9h:
		ret = "wb9h";
		break;
			// using  run-length encoding strategy
	case gz_openmode::wb1R:
		ret = "wb1R";
		break;
	case gz_openmode::wb6R:
		ret = "wb6R";
		break;
	case gz_openmode::wb9R:
		ret = "wb9R";
		break;
			// using  fixed strategy
	case gz_openmode::wb1F:
		ret = "wb1F";
		break;
	case gz_openmode::wb6F:
		ret = "wb6F";
		break;
	case gz_openmode::wb9F:
		ret = "wb9F";
		break;
			// no compression and not using the gzip format
	case gz_openmode::wbT:
		ret = "wbT";
		break;
			// read binary file
	default:
		ret = "error";
	}

	return ret;
}

const gz_openmode_type _to_gz_openmode(char const* val) {
	gz_openmode_type ret = gz_openmode::Enum(0);
	for (size_t _modes = 0; _modes < gz_openmode::_count; _modes++) {
		gz_openmode_type _openmode = static_cast<gz_openmode_type>(_modes);
		if (strcmp(val, gz_openmode::_to_str(_openmode).c_str())) {
			ret =  _openmode;
			break;
		}
	}
	return ret;
}

}
// ----------------------------------------------------------------------------
// Internal classes to implement gzstream. See header file for user classes.
// ----------------------------------------------------------------------------

// --------------------------------------
// class gzfilebuf:
// --------------------------------------

void gzfilebuf::_M_allocate_internal_buffer() {
	if (!_M_buf_allocated && !_M_buf) {
		_M_buf = new char[_M_buf_size];
		_M_buf_allocated = true;
		setp(_M_buf, _M_buf + (_M_buf_size - 1));
		setg(_M_buf + 4,     // beginning of putback area
				_M_buf + 4,     // read position
				_M_buf + 4);    // end position
	}
}

void gzfilebuf::_M_destroy_internal_buffer() throw () {
	if (_M_buf_allocated) {
		delete[] _M_buf;
		_M_buf = NULL;
		_M_buf_allocated = false;
	}
}

gzfilebuf::gzfilebuf() {
	_M_file = (gzFile) 0;
	_M_opened = false;
	_M_buf_size = BUFSIZ;
	_M_buf = (char*) 0;
	_M_buf_allocated = false;
	_M_mode = gz_openmode::Enum(0);
}

gzfilebuf* gzfilebuf::open(char const *name, char const *_mode) {
	gzfilebuf *_ret = NULL;
	if (!is_open()) {
		_M_file = gzopen(name, _mode);
		if (_M_file != 0) {
			_M_allocate_internal_buffer();
			_M_mode = gz_openmode::_to_gz_openmode(_mode);
			_M_opened = true;
			_ret = this;
		}
	}
	return _ret;
}

gzfilebuf* gzfilebuf::open(char const *name, gz_openmode_type const _mode) {
	gzfilebuf *_ret = NULL;
	char const* _l_mode = gz_openmode::_to_str(_mode).c_str();
	this->open(name, _l_mode);
	_ret = this;
	return _ret;
}

gzfilebuf * gzfilebuf::close() throw(){
	gzfilebuf *_ret = NULL;
	if (is_open()) {
		sync();
		_M_opened = false;
		_M_mode = gz_openmode::Enum(0);
		_M_destroy_internal_buffer();
		_M_buf_allocated = false;
		if (gzclose(_M_file) == Z_OK) {
			_ret = this;
		}
	}
	return _ret;
}

int gzfilebuf::underflow()   // used for input buffer only
{
	if (gptr() && (gptr() < egptr())) {
		return *reinterpret_cast<unsigned char *>(gptr());
	}

	if (!strchr( gz_openmode::_to_str(_M_mode).c_str(), 'r') || !_M_opened) {
		return EOF;
	}
	// Josuttis' implementation of inbuf
	int n_putback = gptr() - eback();
	if (n_putback > 4) {
		n_putback = 4;
	}
	memcpy(_M_buf + (4 - n_putback), gptr() - n_putback, n_putback);

	int num = gzread(_M_file, _M_buf + 4, _M_buf_size - 4);
	if (num <= 0) // ERROR or EOF
			{
		return EOF;
	}

	// reset buffer pointers
	setg(_M_buf + (4 - n_putback),   // beginning of putback area
			_M_buf + 4,                 // read position
			_M_buf + 4 + num);          // end of buffer

	// return next character
	return *reinterpret_cast<unsigned char *>(gptr());
}

int gzfilebuf::flush_buffer() {
	// Separate the writing of the buffer from overflow() and
	// sync() operation.
	int w = pptr() - pbase();
	if (gzwrite(_M_file, pbase(), w) != w) {
		return EOF;
	}
	pbump(-w);
	return w;
}

int gzfilebuf::overflow(int c)   // used for output buffer only
		{

	if (!(strchr(gz_openmode::_to_str(_M_mode).c_str(), 'w') || strchr(gz_openmode::_to_str(_M_mode).c_str(), 'a')) || !_M_opened) {
		return EOF;
	}
	if (c != EOF) {
		*pptr() = c;
		pbump(1);
	}
	if (flush_buffer() == EOF) {
		return EOF;
	}
	return c;
}

int gzfilebuf::sync() {
	// Changed to use flush_buffer() instead of overflow( EOF)
	// which caused improper behavior with std::endl and flush(),
	// bug reported by Vincent Ricard.
	if (pptr() && pptr() > pbase()) {
		if (flush_buffer() == EOF) {
			return -1;
		}
	}
	return 0;
}

// --------------------------------------
// class gzstreambase:
// --------------------------------------

gzstreambase::gzstreambase(char const *name, char const *_mode) {
	init(&_M_gzfilebuf);
	open(name, _mode);
}

gzstreambase::gzstreambase(char const *name, gz_openmode_type _mode) {
	init(&_M_gzfilebuf);
	open(name, _mode);
}

gzstreambase::~gzstreambase() {
	_M_gzfilebuf.close();
}

void gzstreambase::open(char const *name, char const *_mode) {

	if (!_M_gzfilebuf.open(name, _mode)) {
		clear(rdstate() | std::ios::badbit);
	}
}

void gzstreambase::open(char const *name, gz_openmode_type _mode) {

	if (!_M_gzfilebuf.open(name, _mode)) {
		clear(rdstate() | std::ios::badbit);
	}
}

void gzstreambase::close() {
	if (_M_gzfilebuf.is_open())
		if (!_M_gzfilebuf.close()) {
			clear(rdstate() | std::ios::badbit);
		}
}

// static method
bool ifgzstream::maybe_gz(const char *fn) {
	unsigned short byt = 0x0000;
	std::ifstream strm(fn, std::ios_base::binary | std::ios_base::in);
	strm.read(reinterpret_cast<char*>(&byt), 2);
	if (byt == 0x1f8b || byt == 0x8b1f) {
		return true;
	}
	return false;
}

void ifgzstream::_init_ifgzstream(char const *name, gz_openmode_type mode){
	bool err;
		if (maybe_gz(name)) {
			gzfilebuf *gzbuf = new gzfilebuf;
			err = gzbuf != gzbuf->open(name, mode);
			buf = gzbuf;
		} else {
			std::filebuf *fbuf = new std::filebuf;
			err = fbuf != fbuf->open(name, std::ios_base::in); // 'mode' is ignored
			buf = fbuf;
		}
		if (!err) {
			rdbuf(buf);
		} else {
			delete buf;
			buf = NULL;
			setstate(std::ios::failbit);
		}
}

ifgzstream::ifgzstream(char const *name, char const *mode) :
		std::istream(0) {
	_init_ifgzstream(name, gz_openmode::_to_gz_openmode(mode) );
}

ifgzstream::ifgzstream(char const *name, gz_openmode_type mode) :
		std::istream(0) {
	_init_ifgzstream(name, mode);
}

// static class member, ofgzstream::default_mode
char const *ofgzstream::default_mode = "zwb6";
//#else
//char const *ofgzstream::default_mode = "w";
//#endif

ofgzstream::ofgzstream(char const *name, char const *mode) :
		std::ostream(0) {
	bool err;
	if (strchr(mode, 'z')) {
		gzfilebuf *gzbuf = new gzfilebuf;
		err = gzbuf != gzbuf->open(name, mode);
		buf = gzbuf;
	} else {
		std::filebuf *fbuf = new std::filebuf;
		err = fbuf != fbuf->open(name, std::ios_base::out); // 'mode' is ignored
		buf = fbuf;
	}
	if (!err) {
		rdbuf(buf);
	} else {
		delete buf;
		buf = NULL;
		setstate(std::ios::failbit);
	}
}

ofgzstream::ofgzstream(char const *name, gz_openmode_type const mode) :
		std::ostream(0) {
	bool err;
	if ( gz_openmode::wb6 == mode ) {
		gzfilebuf *gzbuf = new gzfilebuf;
		err = gzbuf != gzbuf->open(name, mode);
		buf = gzbuf;
	} else {
		std::filebuf *fbuf = new std::filebuf;
		err = fbuf != fbuf->open(name, std::ios_base::out); // 'mode' is ignored
		buf = fbuf;
	}
	if (!err) {
		rdbuf(buf);
	} else {
		delete buf;
		buf = NULL;
		setstate(std::ios::failbit);
	}
}

} // namespace mfem
