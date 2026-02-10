#pragma once
#include "Generic.h"

// This suffix is appended to all header exported delegates
#define HEADER_GENERATED_DELEGATE_SIGNATURE_SUFFIX TEXT("__DelegateSignature")

/** Helper macro that enables passing comma-separated arguments as a single macro parameter */
#define FUNC_CONCAT( ... ) __VA_ARGS__
//
// /** Declare the user's delegate object */
// // NOTE: The last parameter is variadic and is used as the 'template args' for this delegate's classes (__VA_ARGS__)
// #define FUNC_DECLARE_DELEGATE( DelegateName, ... ) \
// typedef TBaseDelegate<__VA_ARGS__> DelegateName;

class Delegate
{
public:
    static void Test();
};

class FDelegateHandle
{
public:
    enum EGenerateNewHandleType
    {
        GenerateNewHandle
    };

    FDelegateHandle()
        : ID(0)
    {
    }

    explicit FDelegateHandle(EGenerateNewHandleType)
        : ID(GenerateNewID())
    {
    }

    bool IsValid() const
    {
        return ID != 0;
    }

    void Reset()
    {
        ID = 0;
    }

private:
    friend bool operator==(const FDelegateHandle& Lhs, const FDelegateHandle& Rhs)
    {
        return Lhs.ID == Rhs.ID;
    }

    friend bool operator!=(const FDelegateHandle& Lhs, const FDelegateHandle& Rhs)
    {
        return Lhs.ID != Rhs.ID;
    }

    friend inline uint32 GetTypeHash(const FDelegateHandle& Key)
    {
        return GetTypeHash(Key.ID);
    }

    static  uint64 GenerateNewID();

    uint64 ID;
};