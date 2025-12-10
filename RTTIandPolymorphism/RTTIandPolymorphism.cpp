#include <iostream>
#include <vector>
#include <memory>

class BaseElement{
    public:
        BaseElement() = default;
        virtual void process() const = 0;
        virtual ~BaseElement() = default;
};

/*NumericalElement (add a member like int value).
StringElement (add a member like std::string data).
FlagElement (a simple class with no extra members).*/
class NumericalElement : public BaseElement{
    public:
        NumericalElement(int val): value(val){};

        void process() const override{
            std::cout<<value <<" will be processed...\n";
        }

        ~NumericalElement() = default;

    private:
        int value;
};

class StringElement : public BaseElement{
    public:
        StringElement(const std::string& ele): data(ele){};

        void process() const override{
            std::cout<<data <<" will be processed...\n";
        }
        ~StringElement() = default;
    
        private:
            std::string data;
};

class FlagElement : public BaseElement{
    public:
        FlagElement() = default;

        void process() const override{
            std::cout<<"simple flag operation is starting...\n";
        }
        ~FlagElement() = default;

};

void analyzeElement (BaseElement* element);

int main(){
    /*In your main function, use a container (like std::vector) to hold smart pointers (e.g., std::unique_ptr) to the BaseElement type.
    Populate the container with instances of all three derived classes.
    Loop through the container and pass the raw pointer (ptr.get()) of each element to your analyzeElement function.*/
    std::vector<std::unique_ptr<BaseElement>> container;
    container.emplace_back(std::make_unique<StringElement>("Test"));
    container.emplace_back(std::make_unique<NumericalElement>(50));
    container.emplace_back(std::make_unique<FlagElement>());

    for(const auto& ele : container){
        analyzeElement(ele.get());
    }
    return 0;
}

/*If it successfully casts to NumericalElement, report that its value will be processed.
If it successfully casts to StringElement, report that its data will be processed.
If it successfully casts to FlagElement, report that a simple flag operation is starting.
If all casts fail (which shouldn't happen with your three classes, but is good practice), report an unknown type error.*/
void analyzeElement (BaseElement* element){
    if (auto numEle = dynamic_cast<NumericalElement*>(element)){
        numEle -> process();
    }
    else if (auto stringEle = dynamic_cast<StringElement*>(element)){
        stringEle -> process();
    }
    else if (auto flagEle = dynamic_cast<FlagElement*>(element)){
        flagEle -> process();
    }
    else{
        throw std::runtime_error("unknown type error\n");
    }
}