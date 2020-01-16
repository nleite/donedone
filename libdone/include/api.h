#ifndef API_H_
#define API_H_
#pragma once
#include "task.h"

namespace done {
void list_tasks_all();
void list_tasks_done();
void list_tasks_due();
void list_tasks_open();
} // namespace done
#endif // API_H_
