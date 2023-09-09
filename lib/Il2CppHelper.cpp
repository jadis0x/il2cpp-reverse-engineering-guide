#include "pch-il2cpp.h"
#include "il2cpp-appdata.h"
#include "Il2CppHelper.h"

Il2CppHelper::Il2CppHelper()
{
	const Il2CppDomain* domain = il2cpp_domain_get();

	const Il2CppAssembly** assemblies;
	size_t size;

	assemblies = il2cpp_domain_get_assemblies(domain, &size);

	assemblyMap.clear();

	for (size_t i = 0; i < size; ++i) {
		const Il2CppAssembly* assembly = assemblies[i];

		if (assembly) {
			const char* assemblyName = il2cpp_image_get_name(assembly->image);
			assemblyMap[assemblyName] = assembly; 
		}
	}
}

// example: UnityEngine.CoreModule.dll
const Il2CppAssembly* Il2CppHelper::FIND_IL2CPP_ASSEMBLY(const std::string _targetil2cppAssembly) 
{
	for (const auto& entry : assemblyMap) {
		if (strcmp(entry.first, _targetil2cppAssembly.c_str()) == 0) {
			return entry.second;
		}
	}
	return nullptr;
}

const Il2CppImage* Il2CppHelper::GET_IL2CPP_IMAGE(const std::string& _targetil2cppAssembly)
{
	for (const auto& entry : assemblyMap) {
		if (strcmp(entry.first, _targetil2cppAssembly.c_str()) == 0) {
			return entry.second->image;
		}
	}

	return nullptr;
}

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

Il2CppObject* Il2CppHelper::GetTypeFromClass(const Il2CppImage* _image, const char* _namespaze, const char* _name)
{
	Il2CppClass* _targetClass = il2cpp_class_from_name(_image, _namespaze, _name);

	if (_targetClass) {
		const Il2CppType* _targetType = il2cpp_class_get_type(_targetClass);

		if (_targetType) {
			Il2CppObject* targetObject = il2cpp_type_get_object(_targetType);

			if (targetObject) {
				return targetObject;
			}
		}
	}

	return nullptr;
}

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

void Il2CppHelper::PrintAssemblyMap()
{
	if (!assemblyMap.empty()) {
		for (const auto& entry : assemblyMap) {
			std::cout << entry.first << ": " << entry.second << std::endl;
		}
	}
}
void Il2CppHelper::SetFieldValue(const std::string& klass_nameassemblydll, const char* namespake, const char* classvalue, const char* name_space, const char* value_class, const char* fieldoffset, void *value)
{
	Il2CppHelper* _Il2CppHelper = new Il2CppHelper();
	// Get the Il2CppImage for "Assembly-CSharp.dll"
	const Il2CppImage* _AssemblyCSharp = _Il2CppHelper->GET_IL2CPP_IMAGE(klass_nameassemblydll);

	// Get the object for the "Menu" class within the "Horror" namespace
	Il2CppObject* _horrorMenuClassObject = _Il2CppHelper->GetTypeFromClass(_AssemblyCSharp, namespake, classvalue);

	// Check if the object exists
	if (_horrorMenuClassObject) {

		// Find the object represented by _horrorMenuClassObject in the app
		auto menuType = app::Object_1_FindObjectOfType_1(reinterpret_cast<app::Type*>(_horrorMenuClassObject), true, nullptr);

		// Check if the object was found
		if (menuType) {

			// Get the Il2CppClass for the "Menu" class
			Il2CppClass* menuClass = il2cpp_class_from_name(_AssemblyCSharp, name_space, value_class);
			if (menuClass == nullptr) return;

			// Get the FieldInfo for the "steamName" field
			FieldInfo* steamNameField = il2cpp_class_get_field_from_name(menuClass, fieldoffset);

			// Check if the field exists
			if (steamNameField) {
				std::cout << "field is exists!!\n";

				// Set the field's value to the new value
				il2cpp_field_set_value(_horrorMenuClassObject, steamNameField, value);
			}
			else {
				std::cout << "field is not exists!\n";
			}
		}
	}
}
