#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <vector>
template<typename T = uint8_t,int Channel = 4>
class Bitmap{
    public:
    Bitmap(int width,int height):storage_(
        height,std::vector<Elem>(width)
    ){

    }
    using Elem = std::array<T, Channel>;

    std::vector<Elem>& operator[](size_t height){ return storage_[height];};
    const std::vector<Elem>& operator[](size_t height)const{ return storage_[height];};

    std::vector<T> flatten()const{
        if(storage_.empty()){
            return {};
        }
        std::vector<T> flat;
        flat.resize(storage_.size() * storage_[0].size() * Channel);
        size_t index{};
        for(auto &row :storage_){
            for(auto &e :row){
                for(auto channel: e){
                    flat[index++] = channel;
                }
            }
        }

        return flat;
    }
    uint32_t height()const{
        return storage_.size();
    }
    uint32_t width()const{
        if(!height()){
            return 0;
        }
        return storage_[0].size();
    }
private:
    std::vector<std::vector<Elem>> storage_;
};