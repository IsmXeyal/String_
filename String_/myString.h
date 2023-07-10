#pragma once

class myString {
private:
	size_t _length = 0;
	size_t _capacity = 16;
	char* _text = nullptr;
	void setText(const char* text);

public:
	myString(); // Default Constructor
	myString(const char* text); // Constructor with Param
	myString(const myString& other); // Copy Constructor
	// Constructor with Param
	myString(const size_t count, const char text);
	myString(const char* text1, const char* text2); // Constructor with 2 Params
	myString substr(size_t pos, size_t count);
	// Copy Assignment operator
	myString& operator=(const myString& other);
	char& front();
	char& back();
	char& at(size_t index);
	size_t capacity() const;
	size_t size() const;
	size_t find(char chr) const;
	size_t rfind(char chr) const;
	void clear();
	void resize(size_t newSize);
	void reserve(size_t newCapacity);
	void shrink_to_fit();
	bool empty() const;
	myString append(const char* text);
	void push_back(const char chr);
	void pop_back();
	void erase(size_t pos, size_t count);
	void replace(size_t pos, size_t count, const char* text);
	int compare(const myString right);

	const char* print() const {
		return _text;
	}

};

void myString::setText(const char* text) {
	if (this->_text != nullptr) {
		delete[]this->_text;
	}
	_length = strlen(text);
	while (_capacity <= _length) {
		this->_capacity += 16;
	}
	this->_text = new char[_length + 1];
	strcpy_s(this->_text, _length + 1, text);
}

myString::myString() {
	this->_text = new char[_capacity];
	this->_text[0] = '\0';
}

myString::myString(const char* text) {
	setText(text);
}

myString::myString(const myString& other) {
	this->_capacity = other._capacity;
	setText(other._text);
}

myString::myString(const size_t count, const char text) {
	_length = count;
	if (count < 16) {
		_capacity = 16;
	}
	else {
		_capacity = count + 16;
	}

	this->_text = new char[_capacity];
	for (size_t i = 0; i < count; i++) {
		this->_text[i] = text;
	}
	this->_text[count] = '\0';
}

myString::myString(const char* text1, const char* text2) {
	size_t len1 = strlen(text1);
	size_t len2 = strlen(text2);
	_length = len1 + len2;

	while (_length >= _capacity) {
		_capacity += 16;
	}

	this->_text = new char[_capacity];

	for (size_t i = 0; i < len1; i++) {
		this->_text[i] = text1[i];
	}

	for (size_t i = 0; i < len2; i++) {
		this->_text[len1 + i] = text2[i];
	}

	this->_text[_length] = '\0';
}

myString myString::substr(size_t pos, size_t count) {
	if (pos > _length) {
		assert(!"Invalid position for substring");
	}

	for (size_t i = pos; i < pos + count; i++) {
		_text[i - pos] = _text[i];
	}
	_text[count] = '\0';

	return _text;
}

myString& myString::operator=(const myString& other) {
	if (this != &other) {
		delete[] _text;
		this->_capacity = other._capacity;
		setText(other._text);
	}
	return *this;
}

char& myString::front() {
	if (empty() == true) {
		assert(!"String is empty!");
	}
	return this->_text[0];
}

char& myString::back() {
	if (empty() == true) {
		assert(!"String is empty!");
	}
	return this->_text[_length - 1];
}

char& myString::at(size_t index) {
	if (index > _length) {
		assert(!"Index out of range!");
	}
	return this->_text[index];
}

size_t myString::capacity() const {
	return _capacity - 1;
}

size_t myString::size() const {
	return _length;
}

size_t myString::find(char chr) const {
	for (size_t i = 0; i < this->_length; i++) {
		if (this->_text[i] == chr) {
			return i;
		}
	}
	return -1;
}

size_t myString::rfind(char chr) const {
	for (size_t i = this->_length - 1; i >= 0; i--) {
		if (this->_text[i] == chr) {
			return i;
		}
	}
	return -1;
}

void myString::clear() {
	delete[] _text;
	_length = 0;
	_capacity = 16;
	this->_text = new char[_capacity];
	this->_text[0] = '\0';
}

void myString::resize(size_t newSize) {
	if (newSize <= _length) {
		_length = newSize;
		this->_text[_length] = '\0';
	}
	else {
		for (size_t i = _length; i < newSize; i++) {
			this->_text[i] = '\0';
		}
		_length = newSize;
	}
}

void myString::reserve(size_t new_capacity) {
	if (new_capacity > _capacity) {
		while (_capacity <= new_capacity)
			_capacity += 16;
	}
}

void myString::shrink_to_fit() {
	_capacity = 16;
	if (_length < _capacity) {
		_capacity = 16;
	}
	else {
		while (_capacity <= _length)
			_capacity += 16;
	}
}

bool myString::empty() const {
	return _length == 0;
}

myString myString::append(const char* text) {
	size_t new_len = _length + strlen(text);
	while (new_len >= _capacity) {
		_capacity += 16;
		char* new_text = new char[_capacity];
		strcpy_s(new_text, _capacity, this->_text);
		delete[] this->_text;
		this->_text = new_text;
	}
	_length = new_len;
	strcat_s(this->_text, _capacity, text);

	return *this;
}

void myString::push_back(const char chr) {
	if (_length + 1 > _capacity) {
		_capacity += 16;
		char* new_text = new char[_capacity];
		strcpy_s(this->_text, _capacity, new_text);
		delete[] this->_text;
		this->_text = new_text;
	}
	this->_text[_length++] = chr;
	this->_text[_length] = '\0';
}

void myString::pop_back() {
	if (_length > 0) {
		_length--;
		this->_text[_length] = '\0';
		return;
	}
	assert(!"String is empty!");
}

void myString::erase(size_t pos, size_t count) {
	if (_capacity - (_length - count) > 16) {
		_capacity -= 16;
	}
	if (pos + count > _length) {
		assert(!"Count is higher!");
	}

	for (size_t i = pos; i < _length - count; i++) {
		_text[i] = _text[i + count];
	}
	_length -= count;
	_text[_length] = '\0';
}

void myString::replace(size_t pos, size_t count, const char* text) {
	if (pos > _length) {
		assert(!"Invalid position for replace!");
	}
	size_t new_len = strlen(text);

	if (_length - count + new_len >= _capacity) {
		while (_length - count + new_len >= _capacity) {
			_capacity += 16;
		}	
		char* new_text = new char[_capacity];

		for (size_t i = 0; i < pos; i++) {
			new_text[i] = this->_text[i];
		}

		for (size_t i = pos + count; i < _length; i++) {
			new_text[i - count + new_len] = this->_text[i];
		}
	}

	for (size_t i = 0; i < new_len; i++) {
		this->_text[pos + i] = text[i];
	}

	_length = _length - count + new_len;
	this->_text[_length] = '\0';
}

int myString::compare(const myString right) {
	size_t len1 = strlen(this->_text);
	size_t len2 = strlen(right._text);
	for (size_t i = 0; i < len2; i++) {
		if (this->_text[i] < right._text[i] || len1 < len2)
			return -1;
		else if (this->_text[i] > right._text[i] || len1 > len2)
			return 1;
		else
			return 0;
	}
}
