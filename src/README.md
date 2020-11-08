# 算法、数据结构的封装实现 
（大小为n的容器，一般下标从0到n-1）
## 0.1 
>binary_indexed_tree，用树状数组实现对一组数据单点修改(O(logN))和区间求和(O(logN))
## 0.2
>新增 lower_bound 和 upper_bound (都是O(logN))，基于二分的查找
## 0.3
>新增 max_heap和min_heap（大、小根堆），支持O(1)查询堆中最大/最小值，O(logN)的插入，O(logN)的弹出堆顶部
## 0.4
>新增 segment_tree(线段树)，支持O(logN)的区域数据修改、查询，lazy_tag减少没必要修改。
## 0.5
>新增shared_ptr实现
## 0.6
>新增unique_ptr实现
>新增vec，类似STL的vector，但是目前无法做到类似vector<vector<T>>的嵌套
