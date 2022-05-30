// Copyright 2022 ExxaVerse LLC. All Rights Reserved.

#include"LibCore.h"
#include"LibNft.h"
#include"Settings.h"
#include"log.h"
#include"Misc/MonitoredProcess.h"
#include"Runtime/Online/HTTP/Public/Http.h"
#include"Runtime/Online/SSL/Public/Ssl.h"
#include"Misc/Base64.h"
#include"JsonObjectConverter.h"


// NFT - Core
// See NEP-171 at https://nomicon.io/Standards/Tokens/NonFungibleToken/Core

void UNearlinkerFunctionLibraryNft::CallNftTransfer(FString const& contract_id, FNearHttpGetBoolCompleteDelegate const& response_handler, FString const& wallet_authorization
	, FString const& receiver_id, FString const& token_id, FString const& approval_id, FString const& memo
	, FString gas, FString deposit
){
	FFunctionCallData function_call;
	function_call.name="nft_transfer";
	function_call.add_parameter(TEXT("receiver_id") , receiver_id );
	function_call.add_parameter(TEXT("token_id")    , token_id    );
	function_call.add_parameter(TEXT("approval_id") , approval_id );
	function_call.add_parameter(TEXT("memo")        , memo        );
	UNearlinkerFunctionLibraryCore::ContractCall(contract_id, function_call, wallet_authorization, [response_handler](FString response, bool request_succeded){
		parse_and_forward(response, request_succeded, response_handler);
	}, gas, deposit);
}

void UNearlinkerFunctionLibraryNft::CallNftTransferCall(FString const& contract_id, FNearHttpGetBoolCompleteDelegate const& response_handler, FString const& wallet_authorization
	, FString const& receiver_id, FString const& token_id, FString const& approval_id, FString const& memo, FString const& msg
	, FString gas, FString deposit
){
	FFunctionCallData function_call;
	function_call.name="nft_transfer_call";
	function_call.add_parameter(TEXT("receiver_id") , receiver_id );
	function_call.add_parameter(TEXT("token_id")    , token_id    );
	function_call.add_parameter(TEXT("approval_id") , approval_id );
	function_call.add_parameter(TEXT("memo")        , memo        );
	function_call.add_parameter(TEXT("msg")         , msg         );
	UNearlinkerFunctionLibraryCore::ContractCall(contract_id, function_call, wallet_authorization, [response_handler](FString response, bool request_succeded){
		parse_and_forward(response, request_succeded, response_handler);
	}, gas, deposit);
}

void UNearlinkerFunctionLibraryNft::ViewNftToken(FString const& contract_id, FNearHttpGetTokenCompleteDelegate const& response_handler, FString const& token_id){
	FFunctionCallData function_call;
	function_call.name="nft_token";
	function_call.add_parameter(TEXT("token_id")    , token_id    );
	UNearlinkerFunctionLibraryCore::ContractView(contract_id, function_call, [response_handler](FString response, bool request_succeded){
		parse_and_forward(response, request_succeded, response_handler);
	});
}

// NFT - Enumeration
// See NEP-181 at https://nomicon.io/Standards/Tokens/NonFungibleToken/Enumeration

void UNearlinkerFunctionLibraryNft::ViewNftTotalSupply(FString const& contract_id, FNearHttpGetIntCompleteDelegate const& response_handler){
	FFunctionCallData function_call;
	function_call.name="nft_total_supply";
	UNearlinkerFunctionLibraryCore::ContractView(contract_id, function_call, [response_handler](FString response, bool request_succeded){
		parse_and_forward(response, request_succeded, response_handler);
	});
}

void UNearlinkerFunctionLibraryNft::ViewNftTokens(FString const& contract_id, FNearHttpGetTokensCompleteDelegate const& response_handler, int from_index, int limit){
	FFunctionCallData function_call;
	function_call.name="nft_tokens";
	function_call.add_parameter(TEXT("from_index") , FString::FromInt(from_index) );
	function_call.add_parameter(TEXT("limit")      , limit                        );
	UNearlinkerFunctionLibraryCore::ContractView(contract_id, function_call, [response_handler](FString response, bool request_succeded){
		parse_and_forward(response, request_succeded, response_handler);
	});
}

void UNearlinkerFunctionLibraryNft::ViewNftSupplyForOwner(FString const& contract_id, FNearHttpGetIntCompleteDelegate const& response_handler, FString const& account_id){
	FFunctionCallData function_call;
	function_call.name="nft_supply_for_owner";
	function_call.add_parameter(TEXT("account_id"), account_id);
	UNearlinkerFunctionLibraryCore::ContractView(contract_id, function_call, [response_handler](FString response, bool request_succeded){
		parse_and_forward(response, request_succeded, response_handler);
	});
}

void UNearlinkerFunctionLibraryNft::ViewNftTokensForOwner(FString const& contract_id, FNearHttpGetTokensCompleteDelegate const& response_handler, FString const& account_id, int from_index, int limit){
	FFunctionCallData function_call;
	function_call.name="nft_tokens_for_owner";
	function_call.add_parameter(TEXT("account_id") , account_id                   );
	function_call.add_parameter(TEXT("from_index") , FString::FromInt(from_index) );
	function_call.add_parameter(TEXT("limit")      , limit                        );
	UNearlinkerFunctionLibraryCore::ContractView(contract_id, function_call, [response_handler](FString response, bool request_succeded){
		parse_and_forward(response, request_succeded, response_handler);
	});
}

// NFT - Approval management
// See NEP-178 at https://nomicon.io/Standards/Tokens/NonFungibleToken/ApprovalManagement

void UNearlinkerFunctionLibraryNft::CallNftApprove(FString const& contract_id, FNearHttpRequestCompleteDelegate const& response_handler, FString const& wallet_authorization
	, FString const& token_id, FString const& account_id, FString const& msg
	, FString gas, FString deposit
){
	FFunctionCallData function_call;
	function_call.name="nft_approve";
	function_call.add_parameter(TEXT("token_id")   , token_id   );
	function_call.add_parameter(TEXT("account_id") , account_id );
	function_call.add_parameter(TEXT("msg")        , msg        );
	UNearlinkerFunctionLibraryCore::ContractCall(contract_id, function_call, wallet_authorization, response_handler, gas, deposit);
}

void UNearlinkerFunctionLibraryNft::CallNftRevoke(FString const& contract_id, FNearHttpRequestCompleteDelegate const& response_handler, FString const& wallet_authorization
	, FString const& token_id, FString const& account_id
	, FString gas, FString deposit
){
	FFunctionCallData function_call;
	function_call.name="nft_revoke";
	function_call.add_parameter(TEXT("token_id")   , token_id   );
	function_call.add_parameter(TEXT("account_id") , account_id );
	UNearlinkerFunctionLibraryCore::ContractCall(contract_id, function_call, wallet_authorization, response_handler, gas, deposit);
}

void UNearlinkerFunctionLibraryNft::CallNftRevokeAll(FString const& contract_id, FNearHttpRequestCompleteDelegate const& response_handler, FString const& wallet_authorization
	, FString const& token_id
	, FString gas, FString deposit
){
	FFunctionCallData function_call;
	function_call.name="nft_revoke_all";
	function_call.add_parameter(TEXT("token_id")   , token_id   );
	UNearlinkerFunctionLibraryCore::ContractCall(contract_id, function_call, wallet_authorization, response_handler, gas, deposit);
}

void UNearlinkerFunctionLibraryNft::ViewNftIsApproved(FString const& contract_id, FNearHttpGetBoolCompleteDelegate const& response_handler, FString const& token_id, FString const& approved_account_id, int approval_id){
	FFunctionCallData function_call;
	function_call.name="nft_is_approved";
	function_call.add_parameter(TEXT("token_id")            , token_id            );
	function_call.add_parameter(TEXT("approved_account_id") , approved_account_id );
	if(approval_id>=0){
	function_call.add_parameter(TEXT("approval_id")         , approval_id         );
	}
	UNearlinkerFunctionLibraryCore::ContractView(contract_id, function_call, [response_handler](FString response, bool request_succeded){
		parse_and_forward(response, request_succeded, response_handler);
	});
}

//

void parse_and_forward(FString response, bool request_succeded, FNearHttpGetTokenCompleteDelegate const& response_handler){
	FNearNonFungibleToken result;
	if(!FJsonObjectConverter::JsonObjectStringToUStruct(response, &result, 0, 0)){
		UE_LOG(LogNearlinker, Error, TEXT("Failed to parse the Inegration Server response as a NEAR token"));
		return;
	}
	response_handler.ExecuteIfBound(result, request_succeded);
}

void parse_and_forward(FString response, bool request_succeded, FNearHttpGetTokensCompleteDelegate const& response_handler){
	TArray<FNearNonFungibleToken> result;
	if(!FJsonObjectConverter::JsonArrayStringToUStruct(response, &result, 0, 0)){
		UE_LOG(LogNearlinker, Error, TEXT("Failed to parse the Inegration Server response as a list of NEAR tokens"));
		return;
	}
	response_handler.ExecuteIfBound(result, request_succeded);
}

