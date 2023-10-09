#include <concepts>
#include <string>
#include <iostream>

template <typename T>
concept long_from_hash = requires(T t) { { t.hash() } -> std::convertible_to<long>; };

template <typename T>
concept to_string = requires(T t) { { t.toString() } -> std::same_as<std::string>; };

template <typename T> 
concept no_VD = (!std::has_virtual_destructor<T>::value);

// I know we could directly combine all concept into one, I just wanted to test this approach
template <typename T>
concept ComplexConcept = (no_VD<T> && long_from_hash<T> && to_string<T>);

class SomeClass {
	int value = 0;
public:
	SomeClass(int v) : value(v) {}
	long hash() {
		return static_cast<long>(value);
	}
	std::string toString() {
		return "Meow";
	}
};

void checking(ComplexConcept auto& something) {
	something.hash();
	std::cout << something.toString() << std::endl;
}

int main() {
	SomeClass cat{ 13 };
	checking(cat);
}