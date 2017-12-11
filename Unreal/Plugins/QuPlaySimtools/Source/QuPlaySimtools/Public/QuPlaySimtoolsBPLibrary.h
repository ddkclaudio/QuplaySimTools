// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once
#include "Networking.h"
#include "Sockets.h"
#include "Engine.h"

#include "Kismet/BlueprintFunctionLibrary.h"
#include "QuPlaySimtoolsBPLibrary.generated.h"

static TSharedPtr<FInternetAddr> RemoteAddr;
static FSocket* SenderSocket;

/* 
*	Function library class.
*	Each function in it is expected to be static and represents blueprint node that can be called in any blueprint.
*
*	When declaring function you can define metadata for the node. Key function specifiers will be BlueprintPure and BlueprintCallable.
*	BlueprintPure - means the function does not affect the owning object in any way and thus creates a node without Exec pins.
*	BlueprintCallable - makes a function which can be executed in Blueprints - Thus it has Exec pins.
*	DisplayName - full name of the node, shown when you mouse over the node and in the blueprint drop down menu.
*				Its lets you name the node using characters not allowed in C++ function names.
*	CompactNodeTitle - the word(s) that appear on the node.
*	Keywords -	the list of keywords that helps you to find node when you search for it using Blueprint drop-down menu. 
*				Good example is "Print String" node which you can find also by using keyword "log".
*	Category -	the category your node will be under in the Blueprint drop-down menu.
*
*	For more info on custom blueprint nodes visit documentation:
*	https://wiki.unrealengine.com/Custom_Blueprint_Node_Creation
*/
UCLASS()
class UQuPlaySimtoolsBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()
	~UQuPlaySimtoolsBPLibrary();

public: // FUNCOES DE REDE

	/** Create socket and connect to the Simtools 2.0
	* @param YourChosenSocketName a simple name to the socket
	* @param TheIP IP address server (local: "127.0.0.1")
	* @param ThePort port server (4123)
	* @return True if successful
	*/
	UFUNCTION(BlueprintCallable, meta = (Keywords = "QuPlay Simtools UDP"), Category = "QuPlay Simtools 2.0 | UDP")
		static bool QuSimtools_Start(const FString & YourChosenSocketName, const FString & TheIP, const int32 ThePort);

	/** Sending data to Simtools 2.0 socket
	* @return True if successful
	*/
	UFUNCTION(BlueprintCallable, meta = (Keywords = "QuPlay Simtools UDP"), Category = "QuPlay Simtools 2.0 | UDP")
		static bool QuSimtools_SendTelemetry(float Roll, float Pitch, float Yaw, float Heave, float Sway, float Surge, float Extra1, float Extra2, float Extra3);
	
	/** Destroy socket and connect to the Simtools 2.0
	*/
	UFUNCTION(BlueprintCallable, meta = (Keywords = "QuPlay Simtools UDP"), Category = "QuPlay Simtools 2.0 | UDP")
		static void QuSimtools_Stop();
};
