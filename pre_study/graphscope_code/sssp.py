# https://graphscope.io/docs/v0.24.0/zh/analytics_engine 如何自己写图算法
import graphscope
from graphscope.dataset import load_p2p_network
from graphscope import sssp
import time
graphscope.set_option(show_log=False)
graph = load_p2p_network(directed=False)
print(graph.schema)
simple_graph = graph.project(vertices={"host": []}, edges=
{"connect": ["dist"]})

start_time = time.time()
sssp_context = sssp(simple_graph, src=6)#单源最短路
# 记录结束时间
end_time = time.time()
# 计算执行时间
execution_time = end_time - start_time
print(f"sssp执行时间为: {execution_time} 秒")


sssp_context.to_dataframe(
selector={"id": "v.id", "dist": "r"}, vertex_range={"begin": 1,
"end": 10}
).sort_values(by="id")
sssp_context.output_to_client("./sssp_result.csv", selector={"id":
"v.id", "dist": "r"})
