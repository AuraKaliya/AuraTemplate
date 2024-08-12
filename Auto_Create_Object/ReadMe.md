# ObjectCreateManager

Templates that automatically build objects on the heap/stack based on the set size



#### example

```c++
void f()
{
    ObjectCreator<double > v1;//Stack
    ObjectCreator<std::array<double, 200> > v2;//Heap
};
```

