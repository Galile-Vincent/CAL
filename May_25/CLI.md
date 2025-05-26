## Two methods to write "Insert"

### Method 1 (Best way)
#### Always insert above the current_line but when all insert stop current_line change to the previous. So in insert we only need to insert the element above current_line. 
#### In here we didn't change current_line's element until the end. 
<pre><code>
Main:
    while (std::getline(std::cin, command)) {
        if (command == ".") {
          break;
        } else {
          if (!buffer.Insert(command)) {
            Error(INVALID_COMMAND);
          }
       }
    }
    buffer.UpdateCur(buffer.GetCurrent() - 1);

Insert:
    vector.insert(current_line - 1)
    current_line++;
</code></pre>
***
### Method 2
#### We insert element above the current_line in the first time. And change the current line into the elment that added. And after that we append new element under the current_line.
#### In here we assign current_line to the element added. 
<pre><code>
Main:
    if (buffer.GetCurrent() != 0) {
        buffer.UpdateCur(buffer.GetCurrent() - 1);
    }

    while (std::getline(std::cin, input)) {
      if (input == ".") {
        break;
       } else {
        if (!buffer.Append(input)) {
          Error(INVALID_COMMAND);
        }
      }
    }

Insert:
    vector.insert(current_line)
    current_line++;
</code></pre>