/**
 * Description: Finds the Dual problem of an LP
 * Maximize $Z = c^T x \leftrightarrow$ Minimize $W = y^T b$
 * s.t. $Ax\leq b \leftrightarrow $ s.t. $A^T y\geq c$
 * and $x\geq 0 \leftrightarrow $ and $y\geq 0$.
 * variables to constraints, constraints to variables.
 * weak duality property: 
 * any feasible solution x of a primal problem
 * and any feasible solution y of the dual problem dual problem 
 * satisfies $c^Tx\leq b^T y$.
 * Strong duality property: 
 * any feasible solution x of a primal problem
 * and any feasible solution y of the dual problem dual problem 
 * satisfies $c^Tx = b^T y$.
 */
#pragma once
