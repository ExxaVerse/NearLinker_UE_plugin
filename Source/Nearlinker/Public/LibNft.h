// Copyright 2022 ExxaVerse LLC. All Rights Reserved.

#pragma once

#include"Kismet/BlueprintFunctionLibrary.h"
#include"Templates/UniquePtr.h"
#include"Interfaces/IHttpRequest.h"
#include<functional>

#include"LibNft.generated.h"

USTRUCT(BlueprintType)
struct FNearNonFungibleTokenMetadata{
	GENERATED_BODY()
 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString title;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString media;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString media_hash;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int copies;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int issued_at;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int expires_at;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int starts_at;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int updated_at;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString extra;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString reference;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString reference_hash;
};

USTRUCT(BlueprintType)
struct FNearNonFungibleToken{
	GENERATED_BODY()
 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Core")
	FString token_id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Core")
	FString owner_id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Metadata")
	FNearNonFungibleTokenMetadata metadata;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Approval Management")
	TMap<FString,int> approved_account_ids;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Royalties and Payouts")
	TMap<FString,int> royalty;
};
 
DECLARE_DYNAMIC_DELEGATE_TwoParams(FNearHttpGetTokensCompleteDelegate, TArray<FNearNonFungibleToken> const&, near_tokens, bool, bConnectedSuccessfully);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FNearHttpGetTokenCompleteDelegate, FNearNonFungibleToken const&, near_token, bool, bConnectedSuccessfully);

UCLASS()
class NEARLINKER_API UNearlinkerFunctionLibraryNft : public UBlueprintFunctionLibrary{
	GENERATED_BODY()
 
//data
public:

//functions
public:
	// NFT - Core
	// See NEP-171 at https://nomicon.io/Standards/Tokens/NonFungibleToken/Core
	
	UFUNCTION(BlueprintCallable, Category="Nearlinker|NFT|Core", meta=(AutoCreateRefTerm="contract_id"))
	static void CallNftTransfer(FString const& contract_id, FNearHttpGetBoolCompleteDelegate const& response_handler, FString const& wallet_authorization
		, FString const& receiver_id, FString const& token_id, FString const& approval_id="None", FString const& memo="None"
		, FString gas="300000000000000", FString deposit="0.000000000000000000000001");
	UFUNCTION(BlueprintCallable, Category="Nearlinker|NFT|Core", meta=(AutoCreateRefTerm="contract_id"))
	static void CallNftTransferCall(FString const& contract_id, FNearHttpGetBoolCompleteDelegate const& response_handler, FString const& wallet_authorization
		, FString const& receiver_id, FString const& token_id, FString const& msg, FString const& approval_id="None", FString const& memo="None"
		, FString gas="300000000000000", FString deposit="0.000000000000000000000001");
	UFUNCTION(BlueprintCallable, Category="Nearlinker|NFT|Core", meta=(AutoCreateRefTerm="contract_id"))
	static void ViewNftToken(FString const& contract_id, FNearHttpGetTokenCompleteDelegate const& response_handler, FString const& token_id);

	// NFT - Enumeration
	// See NEP-181 at https://nomicon.io/Standards/Tokens/NonFungibleToken/Enumeration
	// See NEP-177 at https://nomicon.io/Standards/Tokens/NonFungibleToken/Metadata

	UFUNCTION(BlueprintCallable, Category="Nearlinker|NFT|Enumeration", meta=(AutoCreateRefTerm="contract_id"))
	static void ViewNftTotalSupply(FString const& contract_id, FNearHttpGetIntCompleteDelegate const& response_handler);
	UFUNCTION(BlueprintCallable, Category="Nearlinker|NFT|Enumeration", meta=(AutoCreateRefTerm="contract_id"))
	static void ViewNftTokens(FString const& contract_id, FNearHttpGetTokensCompleteDelegate const& response_handler, int from_index=0, int limit=100);
	UFUNCTION(BlueprintCallable, Category="Nearlinker|NFT|Enumeration", meta=(AutoCreateRefTerm="contract_id"))
	static void ViewNftSupplyForOwner(FString const& contract_id, FNearHttpGetIntCompleteDelegate const& response_handler, FString const& account_id);
	UFUNCTION(BlueprintCallable, Category="Nearlinker|NFT|Enumeration", meta=(AutoCreateRefTerm="contract_id"))
	static void ViewNftTokensForOwner(FString const& contract_id, FNearHttpGetTokensCompleteDelegate const& response_handler, FString const& account_id, int from_index=0, int limit=100);

	// NFT - Approval management
	// See NEP-178 at https://nomicon.io/Standards/Tokens/NonFungibleToken/ApprovalManagement
	
	UFUNCTION(BlueprintCallable, Category="Nearlinker|NFT|Approval Management", meta=(AutoCreateRefTerm="contract_id"))
	static void CallNftApprove(FString const& contract_id, FNearHttpRequestCompleteDelegate const& response_handler, FString const& wallet_authorization
		, FString const& token_id, FString const& account_id, FString const& msg="None"
		, FString gas="300000000000000", FString deposit="0.000000000000000000000001");
	UFUNCTION(BlueprintCallable, Category="Nearlinker|NFT|Approval Management", meta=(AutoCreateRefTerm="contract_id"))
	static void CallNftRevoke(FString const& contract_id, FNearHttpRequestCompleteDelegate const& response_handler, FString const& wallet_authorization
		, FString const& token_id, FString const& account_id
		, FString gas="300000000000000", FString deposit="0.000000000000000000000001");
	UFUNCTION(BlueprintCallable, Category="Nearlinker|NFT|Approval Management", meta=(AutoCreateRefTerm="contract_id"))
	static void CallNftRevokeAll(FString const& contract_id, FNearHttpRequestCompleteDelegate const& response_handler, FString const& wallet_authorization
		, FString const& token_id
		, FString gas="300000000000000", FString deposit="0.000000000000000000000001");
	UFUNCTION(BlueprintCallable, Category="Nearlinker|NFT|Approval Management", meta=(AutoCreateRefTerm="contract_id"))
	static void ViewNftIsApproved(FString const& contract_id, FNearHttpGetBoolCompleteDelegate const& response_handler, FString const& token_id, FString const& approved_account_id, int approval_id=-1);
};

void parse_and_forward(FString response, bool request_succeded, FNearHttpGetTokensCompleteDelegate const& response_handler);
void parse_and_forward(FString response, bool request_succeded, FNearHttpGetTokenCompleteDelegate const& response_handler);
