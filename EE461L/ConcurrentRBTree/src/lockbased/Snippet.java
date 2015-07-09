package lockbased;

public class Snippet {
	protected enum NodeColor { Red, Black, DoubleBlack };

	protected static NodeColor color (final Node<?, ?> n)
	{
	     return n == null ? NodeColor.Black : n.color;
	} 
		
		private Object attemptUpdateNode(final Object newValue,
				  final Node<K, V> n, final Node<K, V> parent) {
				    if (newValue == null) { // removal
				   if (n.value == null)
				     return null;
				   final Object oldValue;
				   synchronized (n) {
				     if (isUnlinked(n.changeOVL))
				       return SpecialRetry;
				     oldValue = n.value;
				     n.value = null; // Transform into route node
				   }
				   if (n.left == null || n.right == null)
				     removeNode(n);
				   return oldValue;
				 } else {  // update
				   synchronized (n) {
				     if (isUnlinked(n.changeOVL))
				       return SpecialRetry;
				     final Object oldValue = n.value;
				     n.value = newValue;
				     return oldValue;
				   }
				 }
				
				private Node<K,V> pushRed(final Node<K,V> g, 
						    final Node<K,V> p, final Node<K,V> n)
						{
						  p.left.color = p.right.color = NodeColor.Black;
						  if (p.color == NodeColor.DoubleBlack) {
						    p.color = NodeColor.Black;
						    return n;
						  } else { // p is black
						    p.color = NodeColor.Red;
						    return g != rootHolder ? g : p;
						} }

						private Node<K, V> rotateOrPushRed(final Node<K, V> n) {
						  final Node<K, V> p = n.parent;
						  final Node<K, V> g = p.parent;
						  if (g == null) {
						    return blackenRoot(n);
						  } else if (color(p) == NodeColor.Red) {
						    fixColorAndRebalance(p);    // For red clusters
						    return n;
						  } else {
						    synchronized (g) {
						      if (isUnlinked(g.changeOVL) || p.parent != g)
						        return n;
						      synchronized (p) {
						        if (isUnlinked(p.changeOVL) || n.parent != p)
						          return n;
						        if (n.color != NodeColor.Red 
						            || p.color == NodeColor.Red)
						          return n;
						        if (color(p.left) == NodeColor.Red
						            && color(p.right) == NodeColor.Red) {
						          return pushRed(g, p, n);
						        } else if (p.left == n)
						          return rebalance_to_Right(g, p, n);
						        else 
						          return rebalance_to_Left(g, p, n);
						} } } }
						
						
						private Node<K, V> rebalance_to_Left(Node<K, V> g, 
								    Node<K, V> p,
								    Node<K, V> n) {
								  synchronized (n) { 
								    final Node<K, V> nL = n.left, nR = n.right; 
								    final NodeColor nLcolor = color(nL), nRcolor = color(nR);
								    final NodeColor pColor = p.color;
								    if (nLcolor != NodeColor.Red 
								      && nRcolor != NodeColor.Red) {
								      return n;
								    } else if (nLcolor == NodeColor.Red
								        && nRcolor == NodeColor.Red) {
								      rotateLeft_nl(g, p, n, nL);19
								      if (pColor == NodeColor.DoubleBlack) {
								        n.color = nR.color = p.color = NodeColor.Black;
								        return p;
								      } else {
								        nR.color = NodeColor.Black; 
								        return g != rootHolder ? g: n;
								      }
								    }
								    else if (nRcolor == NodeColor.Red) { //Prefer a single...
								      rotateLeft_nl(g, p, n, nL);
								      if (pColor == NodeColor.DoubleBlack) {
								        n.color = nR.color = p.color = NodeColor.Black;
								      } else {
								        n.color = NodeColor.Black;
								        p.color = NodeColor.Red;
								      }
								      return p; 
								    } else {    // ... to a double rotation
								       synchronized (nL) {
								         rotateLeftOverRight_nl(g, p, n, nL);
								         if (p.color == NodeColor.DoubleBlack) {
								           nL.color = n.color = p.color = NodeColor.Black;
								           return p;
								         } else if (nLcolor == NodeColor.Red
								             || nRcolor == NodeColor.Red) {
								           n.color = NodeColor.Black; 
								           return g != rootHolder ? g : nL;
								         } else {
								           nL.color = NodeColor.Black;
								           p.color = NodeColor.Red;20
								           return p;
								     } } }
								 } }
						
						 private boolean attempRemoveBlackLeaf(final Node<K, V> n,
								     final Node<K, V> parent, final Node<K, V> g) {
								   final Node<K, V> damaged;
								   Node<K, V> doubleBlackNode = null;
								   synchronized (g) {23
								     if (parent.parent != g || isUnlinked(g.changeOVL))
								       return false;
								     synchronized (parent) {
								       if (n.parent != parent || isUnlinked(parent.changeOVL))
								         return false;
								    // Link g ‐> p ‐> n is locked. Also Link p ‐> s is also 
								    // Colors of g,p,n,s are also locked.
								       synchronized (n) {
								         final NodeColor nColor = n.color;
								         final Node<K, V> nL = n.left;
								         final Node<K, V> nR = n.right;
								         
								         // ... Handle other cases
								           
								         final char nDir = parent.left == n ? Left : Right;
								         final Node<K, V> s = parent.sibling(nDir);
								         synchronized (s) {
								           final Node<K, V> sL = s.left;
								           final Node<K, V> sR = s.right;
								           final Node<K, V>[] result;
								           if (s.color == NodeColor.Red)
								             result = resolveRedSibling(g, parent, s, sL,
								                 sR, nDir);
								           else
								             result = resolveBlackNode(g, parent, s, nDir); 
								           if (result == null)
								             return false;
								           damaged = result[0];
								           doubleBlackNode = result[1];24
								           removeSonLessNode(parent, n);
								           } // Synchronization of s
								       } // Synchronization n
								     } // Synchronization parent
								   } // Synchronization g
								   if (doubleBlackNode != null)
								     correctBlackCount(doubleBlackNode);
								   if (damaged != null)
								fixColorAndRebalance(damaged);
								   return true;
								 }
						
						private Node<K, V>[] resolveRedSibling(final Node<K, V> g,
								  final Node<K, V> parent, final Node<K, V> s, final Node<K, V> sL,
								  final Node<K, V> sR, final char nDir) {
								  final Node<K, V> newS = s.child(nDir); // newS is inner child of s
								  if (newS.color == NodeColor.Red) {
								    return null;
								  }
								  synchronized (newS) {
								    final NodeColor pColor = parent.color;
								    final NodeColor sLColor = color(sL);
								    final NodeColor sRColor = color(sR);
								    if (nDir == Left) {
								      if (sLColor == NodeColor.Red)
								        return null;
								      else if (pColor == NodeColor.DoubleBlack) {
								        if (sRColor == NodeColor.Black)
								          return null;
								        else {
								          parent.color = NodeColor.Black;
								          s.color = NodeColor.Black;
								          sR.color = NodeColor.Black;27
								          rotateLeft_nl(g, parent, s, sL);
								        }
								      } else if (pColor == NodeColor.Red)
								        return null;
								      else { // p is black
								        s.color = NodeColor.Black;
								        parent.color = NodeColor.Red;
								        rotateLeft_nl(g, parent, s, sL);
								      }
								    } else {
								      // ... same for n as right child
								    }
								    // Now without releasing any locks apply the next operation
								    return resolveBlackNode(s, parent, newS, nDir);
								  } // Synchronization newS
								}
						
						private Node<K, V>[] resolveBlackNode(final Node<K, V> g,
								  final Node<K, V> parent, final Node<K, V> s, final char nDir) {
								  final Node<K, V> doubleBlackNode;
								  final Node<K, V> damaged;
								  final Node<K, V> sL = s.left;
								  final Node<K, V> sR = s.right;
								  final NodeColor pColor = parent.color;
								  final NodeColor sLColor = color(sL);
								  final NodeColor sRColor = color(sR);
								  if (s.color == NodeColor.DoubleBlack) {
								    if (pColor == NodeColor.DoubleBlack)
								      return null;  
								    s.color = NodeColor.Black;
								    if (pColor == NodeColor.Red) {
								      parent.color = NodeColor.Black;
								      damaged = parent;
								      doubleBlackNode = null;
								    } else {
								      parent.color = NodeColor.DoubleBlack;
								      damaged = s;
								      doubleBlackNode = parent; 
								    }
								  } else if (sLColor != NodeColor.Red && sRColor != NodeColor.Red) 
								  {
								    if (pColor != NodeColor.DoubleBlack) {
								      s.color = NodeColor.Red;
								      if (pColor == NodeColor.Black) {
								        doubleBlackNode = parent;
								        parent.color = NodeColor.DoubleBlack;
								      } else30
								      {
								        parent.color = NodeColor.Black;
								        doubleBlackNode = null;
								      }

								      if (s.value == null && sL == null && sR == null) {
								        // We can remove s freely
								        removeSonLessNode(parent, s);
								        damaged = parent;
								      } else {
								        damaged = s;
								      }
								    } else {
								      return null;
								    }
								  } else // Rotation cases, similar to rebalance_to_Left
								  {
								    doubleBlackNode = rebalanceSibling(g, parent, s, sL, sR, nDir);
								    damaged = s; 
								  }
								  Node[] result = { damaged, doubleBlackNode };
								  return result;
								}
}
}

