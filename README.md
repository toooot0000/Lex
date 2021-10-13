# Yet Another Immature Language

This is a compiler studying project.

The language syntax is pretty much like this:

```YAIL
# Comments

# Assignment
Let A be 10
Let B be A
Let A be "a string"

If A == B:
    Print True
Else:
    Print False

For i from 1 to 10:
    Print i

Define Find B in A as:
    # Params declaration
    Given A as List of Int
    Given B as Int

    # Main action
    For i, ele of Enumerate A:
        If B == ele:
            Return i
    Return -1

Let A be [1, 2, 3, 4]

Print Find 2 in A
Let C be Find 3 in A
```
