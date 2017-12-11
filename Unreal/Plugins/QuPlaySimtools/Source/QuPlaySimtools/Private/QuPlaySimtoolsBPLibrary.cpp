// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "QuPlaySimtoolsBPLibrary.h"
#include "QuPlaySimtools.h"

UQuPlaySimtoolsBPLibrary::UQuPlaySimtoolsBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

UQuPlaySimtoolsBPLibrary::~UQuPlaySimtoolsBPLibrary()
{
	QuSimtools_Stop();
}



bool UQuPlaySimtoolsBPLibrary::QuSimtools_Start(const FString & YourChosenSocketName, const FString & TheIP, const int32 ThePort)
{
	QuSimtools_Stop();
	SenderSocket = NULL;

	//Create Remote Address.
	RemoteAddr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();

	bool bIsValid;
	RemoteAddr->SetIp(*TheIP, bIsValid);
	RemoteAddr->SetPort(ThePort);

	if (!bIsValid)
	{
		UE_LOG(LogTemp, Error, TEXT("UDP Sender>> ip address was not valid!"));
		return false;
	}

	SenderSocket = FUdpSocketBuilder(*YourChosenSocketName).AsReusable().WithBroadcast();


	//check(SenderSocket->GetSocketType() == SOCKTYPE_Datagram);

	//Set Send Buffer Size
	int32 SendSize = 2 * 1024 * 1024;
	SenderSocket->SetSendBufferSize(SendSize, SendSize);
	SenderSocket->SetReceiveBufferSize(SendSize, SendSize);

	UE_LOG(LogTemp, Log, TEXT("\n\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"));
	UE_LOG(LogTemp, Log, TEXT("****UDP**** Sender Initialized Successfully!!!"));
	UE_LOG(LogTemp, Log, TEXT("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n\n"));

	return true;
}

bool UQuPlaySimtoolsBPLibrary::QuSimtools_SendTelemetry(float Roll, float Pitch, float Yaw, float Heave, float Sway, float Surge, float Extra1, float Extra2, float Extra3)
{
	if (!SenderSocket)
	{
		UE_LOG(LogTemp, Error, TEXT("No sender socket"));
		return false;
	}
	int32 BytesSent = 0;

	TArray<FString> telemetry;
	telemetry.Add(FString::SanitizeFloat(Roll));
	telemetry.Add(FString::SanitizeFloat(Pitch));
	telemetry.Add(FString::SanitizeFloat(Yaw));
	telemetry.Add(FString::SanitizeFloat(Heave));
	telemetry.Add(FString::SanitizeFloat(Sway));
	telemetry.Add(FString::SanitizeFloat(Surge));
	telemetry.Add(FString::SanitizeFloat(Extra1));
	telemetry.Add(FString::SanitizeFloat(Extra2));
	telemetry.Add(FString::SanitizeFloat(Extra3));
	FString ToSend = FString::Join(telemetry,_T(","));
	TCHAR *data = ToSend.GetCharArray().GetData();
	SenderSocket->SendTo((uint8*)TCHAR_TO_UTF8(data), FCString::Strlen(data), BytesSent, *RemoteAddr);

	if (BytesSent <= 0)
	{
		UE_LOG(LogTemp, Error, TEXT("Socket is valid but the receiver received 0 bytes, make sure it is listening properly!"));
		return false;
	}

	return true;
}

void UQuPlaySimtoolsBPLibrary::QuSimtools_Stop()
{
	if (SenderSocket)
	{
		SenderSocket->Close();
		ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(SenderSocket);
	}
}