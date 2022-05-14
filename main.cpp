#include "iostream"
#include <vector>

struct vec3
{ 
	int x = 1;
	int y = 2; 
	int z = 3;
};

std::vector<int>nums = { 1, 2, 3 };
std::vector<int>::iterator itr; // this is an iterator object from the stadard library. it iterates over a container, in this case a std::vector.
std::vector<std::unique_ptr<vec3>> coords; //vector of unique pointers. smart pointers call the destructor of the thing they point to  when they fall out of scope.
//the difference between a unique pointer and a shared pointer is in how many pointers can point to the same object.
//There is a problem with me using dynamically sized arrays here and not specifying the size that we will get to later.

int oops[]{3,4.5};

int main()
{
	//A 'normal' for loop. It follows the pattern "init - condition - iteration" 
	for (int i = 0; i < 3; i++)
	{
		std::cout << "gut expellation" <<"\n";
	}
	//A for loop using std::iterator. It uses much the same syntactical structure as a normal for loop, but the here the start and end of the loop are stored in the
	//iterator object. You can do somthing like this by passing in an outside varable representing the start and end point of the container you are iterating over, this is just more handy. 
	for (itr = nums.begin(); itr != nums.end(); ++itr)
	{
		std::cout << "vomit" <<"\n";
	}
	//This is a range-based for loop. This is just much easier to write than the other ones, but it also solves a problem that the other ones have with the ++ overload.
	//The problem with 'x++' and "++x' is  return i++ returns i, then increments, return ++i increments, then returns i. When iterating over an array
    //this gets weird with user - defined overloads, but worse than that, we basically never want the version of this that returns i then increments.
	//The reason why I dont want to use ++ is because its ambigouous AF and really easy to handwave. I dont want to spend time being paranoid about what version of
	//the ++ operator I decided to use and whether its approprate for the program or whatever, if i can help it. 
	
	//Range based for takes the container right of the colon as input, copies the element at the start of that container into the variable on the left, and then iterates through that container.
	//the container needs a begin and end function to work(which will be important for answering a question later) 
	//It stops before the last element. 
	
	for (int x: oops)
	{
		std::cout << x << "\n";
	}
	// And now we get to the first of the questions about range based for: Why is the ampersand there? Normally, as you see above, you dont need it.
	//BUT in this case we are iterating over a container of pointers to Vec3s, and copying each one into this local p. If we dont defererence, the compiler catches that we tried to
	//copy a pointer into there when  it goes to find std::vector.begin and instead sees 0004464AF, instead.
	//auto is again a nice to have - i can just let the compiler figure out the type. Yes, its a little harder to read, but it means if i change what the container im passing in has in it, i dont
	//also have to change every for loop im passing that container to. Right now, it doesnt matter that much, but itseems to me a nice habit to get into to not write code that breaks 
	//when assumptions change. 
	for (const auto& p : coords)
	{
		std::cout << p->x << "\n";
	}
	//if you like,it could be rewritten as
	for (const std::unique_ptr<vec3>& p : coords)
	{
		std::cout << p->x << "\n";
	}

	//There is a huge problem with these though: because i didnt specify the size(implicily or explicilty) it cant really do anything with the begin and end stuff.
	//I end up finding this out at runtime, which means this for loop fails silently. Not great!
	//in the larger framework, I could do that in the constructor and i guess i could make an explicit contructor for main, but i want to get to a second thing thats related.
	

	std::vector<std::unique_ptr<vec3>> coords2(3); // this actually says what size the vector is, which is good, but... 

	for (const auto& p : coords2)
	{
		//std::cout << p->x << "\n";
	}
	//This still doesnt work because we still need to call the contructor on each object and store it in a pointer to said object.
	//This gets us to the second question which was "why are you using std::make_unique"
	//Well...
	for (auto& p : coords2)
	{
		 p = std::make_unique<vec3>();
		 std::cout << p->y << "\n"; 
	}
	//The reason why we are using std::make unique here is for the same reason we used new before, except that this time we are usng a smart pointer to store it, so its a little easier to use make_unique.
	


	std::cout << "bleh";
}