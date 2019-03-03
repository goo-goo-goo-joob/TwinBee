#pragma once
#include "GameItem.h"
#include "initialization.h"

class Cloud :
	public GameItem
{
    int _speed;
public:
    int haveBell;
    Cloud();
    ~Cloud() override;
    void access(Visitor &v) override;
    void Update(const Notifer& n) override;
    void Move();
};


