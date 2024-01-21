from ng_ai import NebulaReader
from ng_ai.config import NebulaGraphConfig

from nebula3.Config import Config
from nebula3.gclient.net import ConnectionPool
from networkx.algorithms import single_source_dijkstra_path


# read data with nebula/networkx engine, query mode
config_dict = {
    "graphd_hosts": "127.0.0.1:9669",
    "user": "root",
    "password": "nebula",
    "space": "p2p_network",
}
config = NebulaGraphConfig(**config_dict)
reader = NebulaReader(engine="nebula", config=config)
reader.query(edges=["connection"], props=[['dist','src_label_id','dst_label_id']])
g = reader.read()
graph=g.algo.get_graph()
print(graph)
print(single_source_dijkstra_path(graph,source=6))

