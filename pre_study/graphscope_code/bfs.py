# https://graphscope.io/docs/v0.24.0/zh/analytics_engine 如何自己写图算法
import graphscope
from graphscope.dataset import load_p2p_network
from graphscope import sssp
from graphscope import bfs
import time



# 记录开始时间
start_time = time.time()
graphscope.set_option(show_log=False)
graph = load_p2p_network(directed=False)
print(graph.schema)
simple_graph = graph.project(vertices={"host": []}, edges=
{"connect": ["dist"]})
# 记录结束时间
end_time = time.time()
# 计算执行时间
execution_time = end_time - start_time
print(f"载图时间为: {execution_time} 秒")


# 记录开始时间
start_time = time.time()
bfs_context = bfs(simple_graph, src=6)#bfs
# 记录结束时间
end_time = time.time()
# 计算执行时间
execution_time = end_time - start_time
print(f"bfs执行时间为: {execution_time} 秒")

df_bfs = bfs_context.to_dataframe(selector={"id": "v.id", "rank": "r"}, vertex_range={"begin": 1, "end": 10}).sort_values(by="id")
print(df_bfs)
print("BFS completed.")








