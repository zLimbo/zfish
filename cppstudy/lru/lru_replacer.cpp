//===----------------------------------------------------------------------===//
//
//                         BusTub
//
// lru_replacer.cpp
//
// Identification: src/buffer/lru_replacer.cpp
//
// Copyright (c) 2015-2019, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#include "lru_replacer.h"

namespace bustub {

LRUReplacer::LRUReplacer(size_t num_pages) {}

LRUReplacer::~LRUReplacer() = default;

bool LRUReplacer::Victim(frame_id_t *frame_id) {
    if (frame_list_.empty()) {
        return false;
    }
    auto id = frame_list_.front();
    frame_list_.pop_front();
    id2it_.erase(id);
    *frame_id = id;
    return true;
}

void LRUReplacer::Pin(frame_id_t frame_id) {
    auto it = id2it_.find(frame_id);
    if (it == id2it_.end()) {
        return;
    }
    frame_list_.erase(it->second);
    id2it_.erase(it);
}

void LRUReplacer::Unpin(frame_id_t frame_id) {
    //   if (auto it = id2it_.find(frame_id); it != id2it_.end()) {
    //     frame_list_.erase(it->second);
    //   }
    if (id2it_.find(frame_id) != id2it_.end()) {
        return;
    }
    frame_list_.emplace_back(frame_id);
    id2it_[frame_id] = --frame_list_.end();
}

size_t LRUReplacer::Size() { return frame_list_.size(); }

}  // namespace bustub
