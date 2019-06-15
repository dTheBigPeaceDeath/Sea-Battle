class pstring
{
private:
	char *str_char_1;
public:
	pstring()
	{
		str_char_1 = new char [1];
		*str_char_1 = '\0';
	}
	pstring(const char *INstr_char_1)
	{
		int c1 = 0;

		str_char_1 = new char [Length(INstr_char_1) + 1];

		while(c1 < Length(INstr_char_1))
		{
			str_char_1[c1] = INstr_char_1[c1];
			c1++;
		}
		str_char_1[c1] = '\0';
	}
	pstring(pstring &INpstring_str)
	{
		int c1;

		str_char_1 = new char [Length(INpstring_str.str_char_1) + 1];

		for(c1 = 0; c1 < Length(INpstring_str.str_char_1); c1++)
		{
			str_char_1[c1] = *(INpstring_str.str_char_1 + c1);
		}
		str_char_1[c1] = '\0';
	}
	~pstring()
	{
		delete [] str_char_1;
	}
	operator char*() const
	{
		return str_char_1;
	}
	void operator = (const pstring &INpstring_str)
	{
		int c1;

		delete [] str_char_1;
		str_char_1 = new char [Length(INpstring_str.str_char_1) + 1];

		for(c1 = 0; c1 < Length(INpstring_str.str_char_1); c1++)
		{
			str_char_1[c1] = *(INpstring_str.str_char_1 + c1);
		}
		str_char_1[c1] = '\0';
	}
	void operator = (const char *INstr_char_1)
	{
		int c1;

		delete [] str_char_1;
		str_char_1 = new char [Length(INstr_char_1) + 1];

		for(c1 = 0; c1 < Length(INstr_char_1); c1++)
		{
			*(str_char_1 + c1) = *(INstr_char_1 + c1);
		}
		str_char_1[c1] = '\0';
	}
	void operator += (const pstring &INpstring_str)
	{
		int c1 = 0;
		int c2 = 0;
		char *temp;

		temp = new char [Length(str_char_1) + Length(INpstring_str.str_char_1) + 1];

		for(c1 = 0; c1 < Length(str_char_1); c1++)
		{
			*(temp + c1) = *(str_char_1 + c1);
		}

		for(c2 = c1; c2 < Length(str_char_1) + Length(INpstring_str.str_char_1); c2++)
		{
			*(temp + c2) = *(str_char_1 + c2);
		}
		temp[c2] = '\0';

		delete [] str_char_1;
		str_char_1 = temp;
	}
	void operator += (const char *INstr_char_1)
	{
		int c1 = 0;
		int c2 = 0;
		char *temp;

		temp = new char [Length(str_char_1) + Length(INstr_char_1) + 1];
		
		for(c1 = 0; c1 < Length(str_char_1); c1++)
		{
			*(temp + c1) = *(str_char_1 + c1);
		}
		
		for(c2 = 0; c2 < Length(INstr_char_1); c2++)
		{
			*(temp + c2 + c1) = *(INstr_char_1 + c2);
		}
		*(temp + c2 + c1) = '\0';
		
		delete [] str_char_1;
		str_char_1 = temp;
	}
	void operator += (const char INnew_symbol)
	{
		int c1 = 0;
		char *temp;

		temp = new char [Length(str_char_1) + 2];

		for(c1 = 0; c1 < Length(str_char_1); c1++)
		{
			*(temp + c1) = *(str_char_1 + c1);
		}
		temp[c1] = INnew_symbol;
		c1++;
		temp[c1] = '\0';

		delete [] str_char_1;
		str_char_1 = temp;
	}
	bool operator == (const pstring &INpstring_str) const
	{
		bool equal = true;
		int c1;

		for(c1 = 0; str_char_1[c1] != '\0' && INpstring_str.str_char_1[c1] != '\0' && equal; c1++)
		{
			equal = str_char_1[c1] == INpstring_str.str_char_1[c1];
		}

		return equal;
	}
	bool operator == (const char *INstr_char_1) const
	{
		bool R = true;
		int c1;

		for(c1 = 0; str_char_1[c1] != '\0' && INstr_char_1[c1] != '\0' && R; c1++)
		{
			R = str_char_1[c1] == INstr_char_1[c1];
		}

		return R;
	}
	int Length(const char *INstr_char_1)
	{
		int R = 0;

		while(*(INstr_char_1 + R) != '\0')
			R++;

		return R;
	}
	int Length() const
	{
		int R = 0;

		while(*(str_char_1 + R) != '\0')
			R++;

		return R;
	}
	char GetSymbol(const int INsymbol_index)
	{
		char R;

		R = str_char_1[INsymbol_index];

		return R;
	}
};