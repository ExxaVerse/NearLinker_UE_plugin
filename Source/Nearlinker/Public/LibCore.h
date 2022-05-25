// Copyright 2022 ExxaVerse LLC. All Rights Reserved.

#pragma once

#include"Kismet/BlueprintFunctionLibrary.h"
#include"Templates/UniquePtr.h"
#include"Dom/JsonValue.h"
#include"Interfaces/IHttpRequest.h"
#include<functional>

#include"LibCore.generated.h"

class FMonitoredProcess;

USTRUCT(BlueprintType)
struct FFunctionCallData{
	GENERATED_BODY()
 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FString,FString> parameters_string;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FString,int> parameters_int;

	auto add_parameter(FString const& key, FString const& value){return this->parameters_string.Add(key, value);}
	auto add_parameter(FString const& key, int     const& value){return this->parameters_int   .Add(key, value);}
};

USTRUCT(BlueprintType)
struct FContractViewData{
	GENERATED_BODY()
 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FFunctionCallData function;
};

USTRUCT(BlueprintType)
struct FContractCallData{
	GENERATED_BODY()
 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString account_id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString private_key;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FFunctionCallData function;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString gas;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString deposit;
};

DECLARE_DYNAMIC_DELEGATE_TwoParams(FNearHttpRequestCompleteDelegate, FString, Response, bool, bConnectedSuccessfully);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FNearHttpGetIntCompleteDelegate , int , result, bool, bConnectedSuccessfully);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FNearHttpGetBoolCompleteDelegate, bool, result, bool, bConnectedSuccessfully);

UCLASS()
class NEARLINKER_API UNearlinkerFunctionLibraryCore : public UBlueprintFunctionLibrary{
	GENERATED_BODY()
 
//data
public:

//functions
public:
	//Integration Server

	UFUNCTION(BlueprintCallable, Category="Nearlinker|Integration server")
	static void StartIntegrationServer();
	UFUNCTION(BlueprintCallable, Category="Nearlinker|Integration server")
	static void StopIntegrationServer();
	UFUNCTION(BlueprintCallable, Category="Nearlinker|Integration server", meta=(AutoCreateRefTerm="method,resource,data,wallet_authorization"))
	static void SendRequestToIntegrationServer(FString const& method, FString const& resource, FNearHttpRequestCompleteDelegate const& response_handler, FString const& data="");

	static void SendRequestToIntegrationServer(FString const& method, FString const& resource, std::function<void(FString,bool)> const& response_handler, FString const& data="");

	// Core blockchain funtions

	//UFUNCTION(BlueprintCallable, Category="Nearlinker|Core")
	//static void CreateWallet(FString const& wallet_name, FNearHttpRequestCompleteDelegate const& response_handler);
	//UFUNCTION(BlueprintCallable, Category="Nearlinker|Core")
	//static void DeployContract(FNearContract const& contract, FString const& wallet_authorization, FNearHttpRequestCompleteDelegate const& response_handler);
	UFUNCTION(BlueprintCallable, Category="Nearlinker|Core", meta=(AutoCreateRefTerm="contract_id"))
	static void ContractView(FString const& contract_id, FFunctionCallData const& function_description, FNearHttpRequestCompleteDelegate const& response_handler);
	UFUNCTION(BlueprintCallable, Category="Nearlinker|Core", meta=(AutoCreateRefTerm="contract_id"))
	static void ContractCall(FString const& contract_id, FFunctionCallData const& function_description, FString const& wallet_authorization, FNearHttpRequestCompleteDelegate const& response_handler, FString gas="300000000000000", FString deposit="0.000000000000000000000001");

	static void ContractView(FString const& contract_id, FFunctionCallData const& function_description, std::function<void(FString,bool)> const& response_handler);
	static void ContractCall(FString const& contract_id, FFunctionCallData const& function_description, FString const& wallet_authorization, std::function<void(FString,bool)> const& response_handler, FString gas="300000000000000", FString deposit="0.000000000000000000000001");

public:
	static TSharedPtr<FJsonValue> JsonExport(FProperty* Property , const void* Value);
};

void parse_and_forward(FString response, bool request_succeded, FNearHttpGetIntCompleteDelegate const& response_handler);
void parse_and_forward(FString response, bool request_succeded, FNearHttpGetBoolCompleteDelegate const& response_handler);
