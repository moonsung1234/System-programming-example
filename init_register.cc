
#include <iostream>

using namespace std;

//virtual stack struct
typedef struct VirtualStack {
	int value;
	int address;
	bool is_delete;
} VS;

//init stack environment function
VS* initStackEnv(int stack_length, int stack_size) {
	VS* stack = new VS[stack_length];

	for(int i=0; i<stack_length; i+=stack_size) {
		stack[i].address = i;
		stack[i].is_delete = false;
	}

	return stack;
}

//find stack member function
VS* findInStack(VS* stack, int address, const uint32_t stack_length) {
	for(int i=0; i<stack_length; i++) {
		if(stack[i].address == address) {
			return &stack[i];
		}
	}

	return nullptr;
}

//set value in stack function1 (overload)
VS* setValue(VS* in_stack, int value) {
	in_stack->value = value;

	return in_stack;
}

//set value in stack function2 (overload)
VS* setValue(VS* stack, int address, int value, const uint32_t stack_length) {
	for(int i=0; i<stack_length; i++) {
		if(stack[i].address == address) {
			stack[i].value = value;

			return &stack[i];
		}
	}

	return nullptr;
}

//delete continue
VS* deleteForSp(VS* stack, int start_address, const uint32_t stack_length) {
	for(int i=0; i<stack_length; i++) {
		if(stack[i].address > start_address) {
			stack[i].is_delete = true;
		}
	}

	return stack;
}

int main() {
	//default
	const uint32_t STACK_LENGTH = 5;
	const uint32_t STACK_SIZE = 1;
	uint32_t START_ADDRESS = 0;

	//set register &stack
	int sp_register;
	int fp_register;
	VS* stack = initStackEnv(STACK_LENGTH, STACK_SIZE);
	
	//go
	sp_register = setValue(stack, START_ADDRESS, 1234, STACK_LENGTH)->address;
	fp_register = setValue(stack, START_ADDRESS += STACK_SIZE, 0, STACK_LENGTH)->address;
	sp_register = setValue(stack, START_ADDRESS += STACK_SIZE, 5678, STACK_LENGTH)->address;
	fp_register = setValue(stack, START_ADDRESS += STACK_SIZE, fp_register, STACK_LENGTH)->address;
	sp_register = setValue(stack, START_ADDRESS += STACK_SIZE, 9012, STACK_LENGTH)->address;

	//back
	sp_register = deleteForSp(stack, fp_register, STACK_LENGTH)->address;
	fp_register = findInStack(stack, fp_register, STACK_LENGTH)->value;
	sp_register = deleteForSp(stack, fp_register, STACK_LENGTH)->address;
	fp_register = findInStack(stack, fp_register, STACK_LENGTH)->value;
	sp_register = deleteForSp(stack, fp_register, STACK_LENGTH)->address;

	//print state
	for(int i=0; i<STACK_LENGTH; i++) {
		if(stack[i].is_delete != true) {
			cout << "value : " << stack[i].value << endl;
			cout << "address : " << stack[i].address << endl;
		}
	}

	//end 
	delete[] stack;
	return 0;
}