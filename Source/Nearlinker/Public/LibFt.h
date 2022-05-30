// Copyright 2022 ExxaVerse LLC. All Rights Reserved.

#pragma once

#include"Kismet/BlueprintFunctionLibrary.h"
#include"Templates/UniquePtr.h"
#include"Interfaces/IHttpRequest.h"
#include<functional>

#include"LibFt.generated.h"


// FT - Metadata
// See NEP-148 at https://nomicon.io/Standards/Tokens/FungibleToken/Metadata
	
USTRUCT(BlueprintType)
struct FNearFungibleTokenMetadata{
	GENERATED_BODY()
 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString spec;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString symbol;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString icon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString reference;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString reference_hash;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int decimals;
};

UCLASS()
class NEARLINKER_API UNearlinkerFunctionLibraryFt : public UBlueprintFunctionLibrary{
	GENERATED_BODY()
 
//data
public:

//functions
public:
	// FT - Core
	// See NEP-141 at https://nomicon.io/Standards/Tokens/FungibleToken/Core
	
	UFUNCTION(BlueprintCallable, Category="Nearlinker|FT|Core", meta=(AutoCreateRefTerm="contract_id"))
	static void CallFtTransfer(FString const& contract_id, FNearHttpRequestCompleteDelegate const& response_handler, FString const& wallet_authorization
		, FString const& receiver_id, FString const& amount, FString const& memo="None"
		, FString gas="300000000000000", FString deposit="0.000000000000000000000001");
	UFUNCTION(BlueprintCallable, Category="Nearlinker|FT|Core", meta=(AutoCreateRefTerm="contract_id"))
	static void CallFtTransferCall(FString const& contract_id, FNearHttpRequestCompleteDelegate const& response_handler, FString const& wallet_authorization
		, FString const& receiver_id, FString const& amount, FString const& msg, FString const& memo="None"
		, FString gas="300000000000000", FString deposit="0.000000000000000000000001");
	UFUNCTION(BlueprintCallable, Category="Nearlinker|FT|Core", meta=(AutoCreateRefTerm="contract_id"))
	static void ViewFtBalanceOf(FString const& contract_id, FNearHttpRequestCompleteDelegate const& response_handler, FString const& account_id);
	UFUNCTION(BlueprintCallable, Category="Nearlinker|FT|Core", meta=(AutoCreateRefTerm="contract_id"))
	static void ViewFtTotalSupply(FString const& contract_id, FNearHttpRequestCompleteDelegate const& response_handler);

};

