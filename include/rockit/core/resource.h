#pragma once

namespace Rockit
{
    class Resource
    {
    protected:
        bool isValid = false;
    public:
        Resource(bool isValid)
                : isValid(isValid) {};

        bool IsValid();
    };
}