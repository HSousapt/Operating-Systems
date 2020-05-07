typedef struct person{
	char* name;
	int age;
	char state;
}Person;


//void		strToBinary(char*, char*);
//void		intToBinary(int);
//void		binaryToStr(char*);


Person*		init_struct_Person();
void 		insert_new(Person*, char*, int);
void		update(Person*, char*, int);
void 		handle_option(Person*, char*, char*, char*);
void		write_to_file(Person);
