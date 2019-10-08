use std::collections::BTreeMap;
use std::fmt;
use std::rc::Rc;
use std::cell::RefCell;


struct Node {
    key: char,
    ending: bool,
    parent: Option<Rc<RefCell<Node>>>,
    failure: Option<Rc<RefCell<Node>>>,
    children: Rc<RefCell<BTreeMap<char, Rc<RefCell<Node>>>>>
}

impl Node {
    fn new_with(key: char, ending: bool) -> Node {
        Node {
            key,
            ending,
            parent: None,
            failure: None,
            children: Rc::new(RefCell::new(BTreeMap::new()))
        }
    }

    fn new() -> Node {
        Node::new_with(' ', false)
    }
}

impl fmt::Display for Node {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> Result<(), fmt::Error> {
        write!(f, "['{}' {}]", self.key, self.ending)
    }
}

struct ACSearch {
    root: Rc<RefCell<Node>>,
    patterns: Vec<String>
}
impl fmt::Display for ACSearch {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> Result<(), fmt::Error> {
        write!(f, "[{}]", self.patterns.join(", "))
    }
}
impl ACSearch {
    fn new(patterns: Vec<String>) -> ACSearch {
        let mut search: ACSearch = ACSearch {
            root: Rc::new(RefCell::new(Node::new_with(' ', false))),
            patterns
        };
        search._build();
        return search;
    }
    fn _build(&mut self) {
        for pattern in &self.patterns {
            let mut p = self.root.clone();
            for c in pattern.chars() {
                if p.borrow_mut().children.borrow_mut().contains_key(&c) == false {
                    let n = Rc::new(RefCell::new(Node::new_with(c, false)));
                    n.borrow_mut().parent = Some(p.clone());
                    p.borrow_mut().children.borrow_mut().insert(c, n);
                }
                p = p.clone().borrow_mut().children.borrow_mut().get(&c).unwrap().clone();
            }
        }
    }
}

fn main() {
    let patterns = vec!["abc".to_string(), "def".to_string(), "abd".to_string()];
    let search = ACSearch::new(patterns.clone());
    let mut queue = vec![search.root.clone()];
    while queue.is_empty() == false {
        let mut p = queue.pop().unwrap();
        let bp = p.borrow();
        println!("{}", bp);
        for (c,kn) in bp.children.borrow().iter() {
            queue.push(kn.clone());
        }
    }
}
