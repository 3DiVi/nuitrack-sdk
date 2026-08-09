//
//  Copyright © 2025 3divi. All rights reserved.
//

#pragma once

template<typename T>
class Singleton
{
public:
    static std::shared_ptr<T> instance() { return _instance; }

protected:
    static std::shared_ptr<T> _instance;
};
