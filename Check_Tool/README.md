# Check_Tool_Cpp

Templates that AIDS in performing various checks

#### 2024.8.20

update check-function macro

add check-property macro 

* Class

    ```cpp
    class Test
    {
    public:
        void testFunc(){};
        void testFunc(int){};
        int testFunc(double){return 0;};
        int m_id;
        char* m_name;
    }
    ```

* Register

    ```cpp
    //Function
    REGISTER_FUNCTION_FOR_CHECK(testFunc)
    //Property
    REGISTER_PROPERTY_FOR_CHECK(m_name)
    REGISTER_PROPERTY_FOR_CHECK(m_id)
    ```

* Check

    ```cpp
    int main() {
        constexpr bool result = CHECK_FUNCTION_EXIST(Test, myFunc, int,double);
        std::cout << (result ? "Function exists" : "Function does not exist") << std::endl;
        constexpr bool mResult = CHECK_PROPERTY_EXIST(Test, m_id, unsigned int);
        std::cout << (mResult ? "Property exists" : "Property does not exist") << std::endl;
        return 0;
    }
    ```

    



# CheckSameType

* Func

    ```cpp
    template<typename T,typename... Ts>
    constexpr void func()
    {
        if constexpr (isSameType<T,Ts...>())
        {
            std::cout << "same." << std::endl;
        }
        else
        {
            std::cout << "not same." << std::endl;
        }
    }
    ```

* Check

    ```cpp
    
    int main()
    {
        func<int,  int>(); // "same."
        func<int, double, int>(); // "not same."
    	return 0;
    }
    ```

    
