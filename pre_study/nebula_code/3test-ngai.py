from ng_ai import NebulaReader
from ng_ai.config import NebulaGraphConfig

# read data with nebula/networkx engine, query mode
config_dict = {
    "graphd_hosts": "127.0.0.1:9669",
    "user": "root",
    "password": "nebula",
    "space": "demo_basketballplayer",
}
config = NebulaGraphConfig(**config_dict)
reader = NebulaReader(engine="nebula", config=config)
# reader.query(edges=["follow","serve"], props=[["degree"],[]])
g = reader.read()
graph=g.algo.get_graph()
print(graph)
sssp_result=g.algo.shortest_path(source='player102',target='player100')
print(sssp_result)
