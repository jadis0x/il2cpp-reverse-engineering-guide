#pragma once

#include <map>
#include <iostream>
#include <string>



class Il2CppHelper {
public:
	Il2CppHelper();

	const Il2CppAssembly* GetAssembly(const char* _targetil2cppAssembly);

	// example: UnityEngine.CoreModule.dll
	const Il2CppImage* GetImage(const char* _targetil2cppAssembly);

	// example: GetMethodInfo(Assembly-CSharp.dll, SetFOV, 1, "NolanBehaviour", "")
	void GetMethodInfo(const Il2CppImage* _image, const char* _funcName, int argLength, const char* _class_name, const char* _class_namespace = "");

	// example: GetTypeFromClass("UnityEngine.CoreModule.dll", "UnityEngine", "GameObject"); // returns Il2CppObject* 
	Il2CppObject* GetTypeFromClass(const Il2CppImage* _image, const char* _namespaze, const char* _name);

	void GetClassesAndNamesFromAssembly(const Il2CppImage* _image);

	void GetFieldsInformation(Il2CppClass* klass);
	void PrintMethods(Il2CppClass* klass);
	void PrintAssemblyMap();
private:
	 std::map<const char*, const Il2CppAssembly*> assemblyMap;
};
