//
//  Singleton.h
//  nuitrack_sample
//
//  Created by 3DiVi on 13.06.2019.
//  Copyright © 2019 3divi. All rights reserved.
//

#ifndef Singleton_h
#define Singleton_h

template<typename T>
class Singleton
{
public:
    static std::shared_ptr<T> instance()
    {
        return _instance;
    }

protected:
    static std::shared_ptr<T> _instance;
};

#endif /* Singleton_h */
