# Graph Machine Learning
## Knowledge Graph

### KG Representation

| KnowledgeGraph Represent | Define                                                    | scoring func              | symmetric relation | antisymmetric  | inverse               | composition | 1-to-N             |
| ------------------------- | --------------------------------------------------------- | ------------------------- | ------------------ | -------------- | --------------------- | ----------- | ------------------ |
| Translate Embeddings      | $entities,relations\in \mathbb{R}^d$                      | $-norm(h+r-t)$            | no                 | yes (r1=-r2)   | yes   (r3=r1+r2)      | yes         | no                 |
| TransR                    | $entities \in R^d; relation\in R^k, M_r\in R^{k\times d}$ | $-norm(M_rh+r-M_rh)$      | yes (r=0)          | yes($r\neq0$ ) | yes(r1=-r2,Mr1=Mr2)   | no          | yes (proper $M_r$) |
| Dismult                   | $entities,relations\in \mathbb{R}^k$                      | $<h,r,t>$(cosine similar) | yes(naturally)     | no             | no                    | no          | no                 |
| ComplEx                   | $entities,relations\in \mathbb{C}^k$                      | $Re<h,r,\bar{t}>$         | yes(naturally)     | yes            | yes ($r_1=\bar{r_2}$) | no          | yes                |

### KG Reasoning
path-based queries on incomplete KG
- use TransE: query embedding q=h+r, **goal=-||q-t||** 
- query2box: query：$\mathbf{q}=(Center(q),Offset(q))$ a hyper-rectangle that includes all the answers 
  - $Cen(q′)=Cen(q)+Cen(r)$
  - $Off(q′)=Off(q)+Off(r)$
  - score func $f_q(v)=-d_{box}(q,v)=-d_{out}(q,v)-\alpha d_{in}(q,v)$
  - ![Alt text](image.png)
  - how to answer AND-OR queries? rewrite the query in DNF (disjunctino of conjunctive queries) get every answer for the conjunctive and aggregate in the last step.
  - ![Alt text](image-1.png)
  - 
**training**
![Alt text](image-2.png)

## Motifs
### Motif significance
**network motif:** recurring significant patterns  
**significant:**  more frequent then random graph  
**ER random graphs:** n-nodes, each edge appears with probability $p$  
**random graph with certain degree:** randomly pair up nodes with left-over degrees
**node-level subgraph frequency:** number of nodes $u$ in $G_T$, $u$ is part of the isomorphic subgraph to $G_Q$ in $G_T$  
**Z-score for statistical significance:**   
$Z_i=(N_i^{real}-\bar{N}_I^{rand}/std(N_i^{rand}))$  
$N$ is number of motif in graph  
$SP_i=Z_i/\sqrt{\sum_j Z_j^2}$ //normalize $Z_i$

### Neural subgraph representations
subgraph isomorphism is np-hard----use GNN
 to predict  
use **order embedding space** to encode subgraph isomorphism (because isomorphism satisfies transitivity\anti-symmetry\closure)  

**loss function**
![Alt text](image-3.png)
subgraph==lower-left in embedding space  
$E(G_q,G_t)=\sum_{i=1}^D(max(0,z_q[i]-z_t[i]))^2$  
$E$ is zero when $G_q$ is a subgraph

**training**


### mining frequent  motifs