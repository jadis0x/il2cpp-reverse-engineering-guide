
[![GitHub stars](https://img.shields.io/github/stars/jadis0x/il2cpp-reverse-engineering-guide.svg?style=flat&label=Stars&color=ffcc66)](https://github.com/jadis0x/il2cpp-reverse-engineering-guide/stargazers)
[![GitHub contributors](https://img.shields.io/github/contributors/jadis0x/il2cpp-reverse-engineering-guide.svg)](https://github.com/jadis0x/il2cpp-reverse-engineering-guide/graphs/contributors)
[![License](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)

<h3 align="center">Il2cppInspector: C++ Scaffold Guide</h3>

<p>Hello! I have decided to share some useful examples regarding the usage of Il2cppInspector C++ scaffold. In this guide, I will provide examples of how to interact with defined Il2cpp API functions.</p>

### Installation
You can get the latest version of Il2CppInspector 2023.1 [here](https://github.com/jadis0x/il2cpp-reverse-engineering-guide/releases/tag/2023.1).

### Requirements
Having knowledge of C++ and C# is essential. You should also be familiar with the basics of the Unity game engine.

> [!NOTE]  
> I wrote my own helper class. You can access it under the lib folder. Throughout the guide, I will be using the helper functions I created.

  
## Video
[![Video](https://img.youtube.com/vi/L7s2ttcNEh0/0.jpg)](https://www.youtube.com/watch?v=L7s2ttcNEh0)

## Contact
If you have any questions, feel free to reach out to me.</br>

Discord: Jadis0x </br>
Steam: Jadis0x

## Examples
> [!TIP]
> You can find more detailed examples by taking a look at [HERE](https://github.com/ALittlePatate/DevourClient) using the Il2cppInspector analysis tool I used to create the cheat.

## Contents

<nav>
  <ul>
    <li><a href="#get_assemblies">Get the assemblies</a></li>
    <li><a href="#type_usage">Getting the type from a class (Il2CppObject* to Type*)</a></li>
    <li><a href="#get_class_names_types">Getting class names and types from a specific assembly</a></li>
    <li><a href="#get_info_method">Getting information about any method</a></li>
    <li><a href="#call_function">Calling a function with "il2cpp_runtime_invoke"</a></li>
    <li><a href="#list_all_functions">Getting a List of All Functions in the Target Class</a></li>
    <li><a href="#get_field_info">Getting Information about Class Fields (FieldInfo)</a></li>
    <li><a href="#modify_field">Modifiying the Value of a Field</a></li>
  </ul>
</nav>

<br><br>

<h2 id="get_assemblies">Get the assemblies</h2>

<span>This code snippet demonstrates how to retrieve a list of all assemblies within the active domain using il2cpp API functions.</span>

```cpp
// Get the active domain
const Il2CppDomain* domain = il2cpp_domain_get();

// Define variables to hold the assembly list
const Il2CppAssembly** assemblies;
size_t size;

// Use the il2cpp_domain_get_assemblies function to retrieve all assemblies
assemblies = il2cpp_domain_get_assemblies(domain, &size);

// Iterate through each assembly in the list
for (size_t i = 0; i < size; ++i) {
    const Il2CppAssembly* assembly = assemblies[i];

    if (assembly) {
        // Get the assembly name using il2cpp_image_get_name function
        const char* assemblyName = il2cpp_image_get_name(assembly->image);
        
        // Print the name of the assembly to the console
        std::cout << assemblyName << "\n";
    }
}
```

<h2>Summary of Get the assemblies</h2>

<ol>
    <li>
        <strong>Get the Active Domain:</strong>
        <ul>
            <li><strong>Function:</strong> <code>il2cpp_domain_get</code></li>
            <li><strong>Description:</strong> Retrieves the active domain (<code>Il2CppDomain</code>) where the program is currently running.</li>
        </ul>
    </li>
    <li>
        <strong>Retrieve Assemblies:</strong>
        <ul>
            <li><strong>Function:</strong> <code>il2cpp_domain_get_assemblies</code></li>
            <li><strong>Description:</strong> Retrieves a list of all assemblies (<code>Il2CppAssembly</code>) within the specified domain (<code>Il2CppDomain</code>). The function returns an array of <code>Il2CppAssembly</code> pointers (<code>assemblies</code>) and updates the <code>size</code> variable with the number of assemblies found.</li>
        </ul>
    </li>
    <li>
        <strong>Iterate Through Assemblies:</strong>
        <ul>
            <li>Using a <code>for</code> loop, iterate through each assembly in the <code>assemblies</code> array.</li>
        </ul>
    </li>
    <li>
        <strong>Get Assembly Name:</strong>
        <ul>
            <li><strong>Function:</strong> <code>il2cpp_image_get_name</code></li>
            <li><strong>Description:</strong> Retrieves the name of the assembly associated with the given image (<code>Il2CppImage</code>) within the assembly structure (<code>Il2CppAssembly</code>). It returns a <code>const char*</code> containing the assembly name.</li>
        </ul>
    </li>
    <li>
        <strong>Print Assembly Names:</strong>
        <ul>
            <li>Print each assembly name retrieved from <code>il2cpp_image_get_name</code> to the console (<code>std::cout</code>).</li>
        </ul>
    </li>
</ol>

<p>Output: </p>
<img src="img/1.png" width="650">

<br><br>

<h2 id="type_usage">Getting the type from a class (Il2CppObject* to Type*)</h2>

To obtain the type information here, we will use the GetTypeFromClass function inside my Il2cppHelper class.

```cpp
Il2CppObject* Il2CppHelper::GetTypeFromClass(const Il2CppImage* _image, const char* _namespaze, const char* _name)
{
    // Retrieve the class information using the image, namespace, and class name
    Il2CppClass* _targetClass = il2cpp_class_from_name(_image, _namespaze, _name);

    // If the class is found
    if (_targetClass) {
        // Get the type information from the class
        const Il2CppType* _targetType = il2cpp_class_get_type(_targetClass);

        // If the type information is found
        if (_targetType) {
            // Get the Il2CppObject from the type information
            Il2CppObject* targetObject = il2cpp_type_get_object(_targetType);

            // If the object is successfully retrieved, return it
            if (targetObject) {
                return targetObject;
            }
        }
    }

    // If any step fails, return nullptr
    return nullptr;
}
```

<span>First, load the CoreModule from Unity, which contains many fundamental classes such as GameObject.</span>

```cpp
const Il2CppImage* _CoreModule = _helper->GetImage("UnityEngine.CoreModule.dll");
```

<span>If the module is successfully loaded, use the GetTypeFromClass function to get the type information for the GameObject class.</span>

```cpp
if (_CoreModule) {
    // Get the type information for the GameObject class in the UnityEngine namespace
    Il2CppObject* _object = _helper->GetTypeFromClass(_CoreModule, "UnityEngine", "GameObject");

    // If the type information is successfully retrieved
    if (_object) {
        // Cast the Il2CppObject to Type
        Type* gameobjectType = reinterpret_cast<Type*>(_object);

        // If the type casting is successful
        if (gameobjectType) {
            // Find all objects of the GameObject type
            Object_1__Array* getAllGameObjects = Object_1_FindObjectsOfType(gameobjectType, nullptr);

            // Print the count of GameObject instances
            std::cout << "Gameobject count: " << getAllGameObjects->max_length << "\n";

            // If any GameObject instances are found
            if (getAllGameObjects) {
                // Iterate through each GameObject instance
                for (int i = 0; i < getAllGameObjects->max_length; i++) {
                    Object_1* currentGameObject = getAllGameObjects->vector[i];

                    // If the GameObject is active in the hierarchy
                    if (GameObject_get_activeInHierarchy(reinterpret_cast<GameObject*>(currentGameObject), nullptr)) {
                        // Print the name of the active GameObject
                        std::cout << "GameObject Name: " << il2cppi_to_string(Object_1_GetName(currentGameObject, nullptr)) << "\n";
                    }
                }
            }
        }
    }
}
```

<span>In this example, we are passing the type of the object to be found (GameObject) as a parameter to the Object_1_FindObjectsOfType function. This actually allows us to achieve the following:</span>

```cpp
GameObject[] allGameObjects = FindObjectsOfType<GameObject>();
```

> This function is quite slow. Using this function every frame is not recommended.

<h2>Summary of the Steps and il2cpp API Functions Used</h2>

<ol>
  <li>Loading the Image:
    <ul>
      <li>Function: <code>GetImage</code></li>
      <li>Description: Loads the <code>CoreModule</code> image from Unity, which contains fundamental classes like <code>GameObject</code>.</li>
    </ul>
  </li>
  <li>Retrieving Class Information:
    <ul>
      <li>Function: <code>il2cpp_class_from_name</code></li>
      <li>Description: Retrieves class information using the image, namespace, and class name.</li>
    </ul>
  </li>
  <li>Getting Type Information from Class:
    <ul>
      <li>Function: <code>il2cpp_class_get_type</code></li>
      <li>Description: Obtains the type information from the class.</li>
    </ul>
  </li>
  <li>Getting Il2CppObject from Type:
    <ul>
      <li>Function: <code>il2cpp_type_get_object</code></li>
      <li>Description: Converts type information into an <code>Il2CppObject</code>.</li>
    </ul>
  </li>
  <li>Casting Il2CppObject to Type:
    <ul>
      <li>Operation: <code>reinterpret_cast&lt;Type*&gt;</code></li>
      <li>Description: Casts the retrieved <code>Il2CppObject</code> to <code>Type</code>.</li>
    </ul>
  </li>
  <li>Finding Objects of a Specific Type:
    <ul>
      <li>Function: <code>Object_1_FindObjectsOfType</code></li>
      <li>Description: Finds all objects of the specified type (<code>GameObject</code> in this case).</li>
    </ul>
  </li>
  <li>Checking if GameObject is Active:
    <ul>
      <li>Function: <code>GameObject_get_activeInHierarchy</code></li>
      <li>Description: Checks if the <code>GameObject</code> is active in the hierarchy.</li>
    </ul>
  </li>
  <li>Getting GameObject Name:
    <ul>
      <li>Function: <code>Object_1_GetName</code></li>
      <li>Description: Retrieves the name of the <code>GameObject</code>.</li>
    </ul>
  </li>
</ol>

<p>Output: </p>
<img src="img/2.png" alt="Gameobjects" width="650">

<br><br>

<h2 id="get_class_names_types">Getting class names and types from a specific assembly</h2>

<p>This code snippet demonstrates how to retrieve and print the names and namespaces of classes within a specified assembly using il2cpp API functions.</p>

```cpp
void Il2CppHelper::GetClassesAndNamesFromAssembly(const Il2CppImage* _image)
{
	if (_image) {
		size_t classCount = il2cpp_image_get_class_count(_image);

		std::cout << "{\n";

		for (size_t i = 0; i < classCount; ++i) {
			const Il2CppClass* _klass = il2cpp_image_get_class(_image, i);

			if (_klass) {
				char* _name = const_cast<char*>(il2cpp_class_get_name(const_cast<Il2CppClass*>(_klass)));
				char* _namespace = const_cast<char*>(il2cpp_class_get_namespace(const_cast<Il2CppClass*>(_klass)));

				std::cout << " [\n";
				std::cout << "\tName: " << _name << "\n";
				std::cout << "\tNamespace: " << _namespace << "\n";

				std::cout << " ],\n";
			}
		}

		std::cout << "\n}\n";
	}
}
```


```cpp
const Il2CppImage* _BoltDll = _helper->GetImage("bolt.dll");

if (_BoltDll) {
    _helper->GetClassesAndNamesFromAssembly(_BoltDll);
}
```

or

```cpp
const Il2CppImage* _assemblyCSHARP = _helper->GetImage("Assembly-CSharp.dll");

if (_assemblyCSHARP) {
   _helper->GetClassesAndNamesFromAssembly(_assemblyCSHARP);
}
```

<p>Outputs: </p>
<img src="img/3.png" width="650">
<img src="img/4.png" width="650">

<br><br>

<h2 id="get_info_method">Getting information about any method </h2>

* It allows you to print the name, return type, and parameter information of the target method.

```cpp
void Il2CppHelper::GetMethodInfo(const Il2CppImage* _image, const char* _funcName, int argLength, const char* _class_name, const char* _class_namespace)
{
	Il2CppClass* _class = il2cpp_class_from_name(_image, _class_namespace, _class_name);

	if (_class == nullptr) return;

	const MethodInfo* methodInfo = il2cpp_class_get_method_from_name(_class, _funcName, argLength);

	if (methodInfo == nullptr) return;

	Il2CppReflectionMethod* reflectionMethod = il2cpp_method_get_object(methodInfo, _class);

	// Check if the reflectionMethod is not null
	if (reflectionMethod == nullptr) return;

	std::cout << "{\n";

	// Get the method's name from the reflectionMethod object
	const char* methodName = il2cpp_method_get_name(methodInfo);
	std::cout << "\tMethod Name: " << methodName << std::endl;

	const Il2CppType* returnType = il2cpp_method_get_return_type(methodInfo);
	std::cout << "\tReturn Type: " << il2cpp_type_get_name(returnType) << std::endl;

	// Get the parameter count of the method using il2cpp_method_get_param_count
	int parameterCount = il2cpp_method_get_param_count(methodInfo);
	std::cout << "\tParameter Count: " << parameterCount << std::endl;

	std::cout << "\t[\n";
	// Get the parameter types of the method
	for (int i = 0; i < parameterCount; i++) {
		// Get the parameter type at index i using il2cpp_method_get_param
		const Il2CppType* parameterType = il2cpp_method_get_param(methodInfo, i);

		// Get the type name of the parameter type using il2cpp_type_get_name
		const char* parameterTypeName = il2cpp_type_get_name(parameterType);

		// Print the parameter type name to the console
		std::cout << "\t\tParameter " << i << " Type: " << parameterTypeName << std::endl;
	}
	std::cout << "\t]\n";

	std::cout << "}\n";
}
```


```cpp
const Il2CppImage* _AssemblyCSharp = _helper->GetImage("Assembly-CSharp.dll");
			
_helper->GetMethodInfo(_AssemblyCSharp, "SetFOV", 1, "NolanBehaviour", "");
```

<p>Output: </p>
<img src="img/5.png" width="650">

<br><br>

<h2 id="call_function">Calling a function with "il2cpp_runtime_invoke"</h2> 

```cpp
if (GetAsyncKeyState(VK_F1) & 0x8000) {
	const Il2CppImage* _AssemblyCSharp = _helper->GetImage("Assembly-CSharp.dll");
	_helper->GetMethodInfo(_AssemblyCSharp, "SetRank", 1, "NolanRankController", "");
}

if (GetAsyncKeyState(VK_F2) & 0x8000) {
	const Il2CppImage* _csharp = _helper->GetImage("Assembly-CSharp.dll");
	if (_csharp == nullptr) return;

	Il2CppObject* nolanObj = _helper->GetTypeFromClass(_csharp, "", "NolanRankController");

	Type* TNolan = reinterpret_cast<Type*>(nolanObj);
	
	auto isTypeValid = Object_1_FindObjectOfType(TNolan, nullptr);

	if(isTypeValid){
	
		NolanBehaviour* _nb_ = reinterpret_cast<NolanBehaviour*>(isTypeValid);

		if (_nb_) {
			Il2CppClass* _nbClass = il2cpp_class_from_name(_csharp, "", "NolanRankController");
			if (_nbClass == nullptr) return;

			const MethodInfo* methodInfo = il2cpp_class_get_method_from_name(_nbClass, "SetRank", 1);

			int newRankvalue = 666;

			void* params[] = { &newRankvalue };

			std::cout << "call function..\n";
			il2cpp_runtime_invoke(methodInfo, _nb_, params, nullptr);
		}
	}
}
```

<p>Output: </p>
<img src="img/6.png" width="650">

<br><br>

<h2 id="list_all_functions">Getting a List of All Functions in the Target Class</h2>

* This function, serves the purpose of obtaining and displaying a list of all methods within a given class (specified by the klass parameter). It iterates through each method in the class using a loop, retrieving information such as the method name and its return type. Subsequently, it prints out the method name along with its return type, providing a clear representation of the methods contained within the class

```cpp
void Il2CppHelper::PrintMethods(Il2CppClass* klass) {
	const MethodInfo* methodIter = nullptr;
	void* iter = nullptr;

	// Retrieve all methods of the class
	while ((methodIter = il2cpp_class_get_methods(klass, &iter)) != nullptr) {
		// Get the name of the method
		const char* methodName = il2cpp_method_get_name(methodIter);

		// Get the return type of the method
		const Il2CppType* methodReturnType = il2cpp_method_get_return_type(methodIter);
		char* returnTypeName = il2cpp_type_get_name(methodReturnType);

		// Print the method name and its return type
		std::cout << "Method Name: " << methodName;
		std::cout << " (" << returnTypeName << ")\n------------------------------------\n";

		// Perform necessary memory operations
		il2cpp_free(returnTypeName);
	}
}
```

## Example:

```cpp
const Il2CppImage* _image = _helper->GetImage("Assembly-CSharp.dll");

if (_image) {
	Il2CppClass* nolanRankControllerClass = il2cpp_class_from_name(_timage, "", "NolanRankController");

	if (nolanRankControllerClass != nullptr) {
		_helper->PrintMethods(nolanRankControllerClass);
	}
}
```

<p>Output: </p>
<img src="img/8.png" width="650">

<br><br>

<h2 id="get_field_info">Getting Information about Class Fields (FieldInfo)</h2>

* It allows us to get information about the fields of a class

```cpp
void Il2CppHelper::GetFieldsInformation(Il2CppClass* klass)
{
	void* iter = nullptr;
	FieldInfo* field = nullptr;

	// Iterate through the fields of the class
	while ((field = il2cpp_class_get_fields(klass, &iter)) != nullptr)
	{
		// Get the name of the field
		const char* fieldName = il2cpp_field_get_name(field);

		// Get the type of the field
		const Il2CppType* fieldType = il2cpp_field_get_type(field);
		char* fieldTypeStr = il2cpp_type_get_name(fieldType);

		// Print the information about the field
		std::cout << "Field Name: " << fieldName << std::endl;
		std::cout << "Type: " << fieldTypeStr << std::endl;
		std::cout << "-----------\n";
	}
}
```


```cpp
const Il2CppImage* _assemblyCSHARP = _helper->GetImage("Assembly-CSharp.dll");
			
if (_assemblyCSHARP) {
	Il2CppClass* _nolanBehaviourClass = il2cpp_class_from_name(_assemblyCSHARP, "", "NolanBehaviour");

	_helper->GetFieldsInformation(_nolanBehaviourClass);
}
```

<p>Output: </p>
<img src="img/7.png" width="650">

<br><br>

<h2 id="modify_field">Modifiying the Value of a Field</h2>

```cpp
if (GetAsyncKeyState(VK_F1) & 0x8000) {
	// Get the Il2CppImage for "Assembly-CSharp.dll"
	const Il2CppImage* _AssemblyCSharp = _helper->GetImage("Assembly-CSharp.dll");

	// Get the object for the "Menu" class within the "Horror" namespace
	Il2CppObject* _horrorMenuClassObject = _helper->GetTypeFromClass(_AssemblyCSharp, "Horror", "Menu");

	// Check if the object exists
	if (_horrorMenuClassObject) {

		// Find the object represented by _horrorMenuClassObject in the app
		auto menuType = app::Object_1_FindObjectOfType_1(reinterpret_cast<Type*>(_horrorMenuClassObject), true, nullptr);

		// Check if the object was found
		if (menuType) {

			// Get the Il2CppClass for the "Menu" class
			Il2CppClass* menuClass = il2cpp_class_from_name(_AssemblyCSharp, "Horror", "Menu");
			if (menuClass == nullptr) return;

			// Get the FieldInfo for the "steamName" field
			FieldInfo* steamNameField = il2cpp_class_get_field_from_name(menuClass, "steamName");

			// Check if the field exists
			if (steamNameField) {
				std::cout << "field is exists!!\n";

				// Define a new value for the field
				const char* newSteamNameValue = "il2cpp-field";

				// Create a new Il2CppString from the new value
				Il2CppString* newSteamNameString = il2cpp_string_new(newSteamNameValue);

				// Set the field's value to the new value
				il2cpp_field_set_value(_horrorMenuClassObject, steamNameField, newSteamNameString);
			}
			else {
				std::cout << "field is not exists!\n";
			}
		}
	}
}
```

I will continue to contribute as much as I can. For now, bye!
