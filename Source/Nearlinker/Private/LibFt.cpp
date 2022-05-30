// Copyright 2022 ExxaVerse LLC. All Rights Reserved.

#include"LibCore.h"
#include"LibFt.h"
#include"Settings.h"
#include"log.h"
#include"Misc/MonitoredProcess.h"
#include"Runtime/Online/HTTP/Public/Http.h"
#include"Runtime/Online/SSL/Public/Ssl.h"
#include"Misc/Base64.h"
#include"JsonObjectConverter.h"


// NFT - Core
// See NEP-171 at https://nomicon.io/Standards/Tokens/NonFungibleToken/Core

void UNearlinkerFunctionLibraryFt::CallFtTransfer(FString const& contract_id, FNearHttpRequestCompleteDelegate const& response_handler, FString const& wallet_authorization
	, FString const& receiver_id, FString const& amount, FString const& memo
	, FString gas, FString deposit
){
	FFunctionCallData function_call;
	function_call.name="ft_transfer";
	function_call.add_parameter(TEXT("receiver_id") , receiver_id );
	function_call.add_parameter(TEXT("amount")      , amount      );
	function_call.add_parameter(TEXT("memo")        , memo        );
	UNearlinkerFunctionLibraryCore::ContractCall(contract_id, function_call, wallet_authorization, response_handler, gas, deposit);
}

void UNearlinkerFunctionLibraryFt::CallFtTransferCall(FString const& contract_id, FNearHttpRequestCompleteDelegate const& response_handler, FString const& wallet_authorization
	, FString const& receiver_id, FString const& amount, FString const& memo, FString const& msg
	, FString gas, FString deposit
){
	FFunctionCallData function_call;
	function_call.name="ft_transfer_call";
	function_call.add_parameter(TEXT("receiver_id") , receiver_id );
	function_call.add_parameter(TEXT("amount")      , amount      );
	function_call.add_parameter(TEXT("memo")        , memo        );
	function_call.add_parameter(TEXT("msg")         , msg         );
	UNearlinkerFunctionLibraryCore::ContractCall(contract_id, function_call, wallet_authorization, response_handler, gas, deposit);
}

void UNearlinkerFunctionLibraryFt::ViewFtBalanceOf(FString const& contract_id, FNearHttpRequestCompleteDelegate const& response_handler, FString const& account_id){
	FFunctionCallData function_call;
	function_call.name="ft_balance_of";
	function_call.add_parameter(TEXT("account_id") , account_id   );
	UNearlinkerFunctionLibraryCore::ContractView(contract_id, function_call, response_handler);
}
void UNearlinkerFunctionLibraryFt::ViewFtTotalSupply(FString const& contract_id, FNearHttpRequestCompleteDelegate const& response_handler){
	FFunctionCallData function_call;
	function_call.name="ft_total_supply";
	UNearlinkerFunctionLibraryCore::ContractView(contract_id, function_call, response_handler);
}


