# Non-Deterministic Turing Machine Simulator

class Queue():
    def __init__(self):
        self.queue = []

    def enqueue(self, state, head, string, iter_count):
        self.queue.append((state, head, string, iter_count))

    def dequeue(self):
        item = self.queue[0]
        self.queue = self.queue[1:]
        return item

    def is_empty(self):
        return len(self.queue) == 0

class TuringMachine():
    def __init__(self, transitions, accepted_states, max_iterations):
        self.transitions = transitions
        self.accepted_states = accepted_states
        self.max_iterations = max_iterations

    def validate_string(self, string):
        head = 0
        state = self.transitions[0][0]
        iter_count = 1

        self.queue = Queue()
        self.queue.enqueue(head, state, string, iter_count)

        outputs = self.validate_symbol()
        return self.output(outputs)

    def validate_symbol(self):
        if self.queue.is_empty():
            return [0]

        
        (state, head, string, iter_count) = self.queue.dequeue()
        outputs = []
        symbol = string[head]

        for (current_state, current_symbol, next_symbol, move, next_state) in self.transitions:
            if state == current_state and (symbol == current_symbol or current_symbol == 'x'):
                if next_state in accepted_states and head == len(string) - 1:
                    return [1]

                if iter_count > max_iterations:
                    outputs = outputs + ['u']
                else:
                    head_copy, string_copy = head, string

                    if next_symbol != 'x':
                        string_copy[head] = next_symbol

                    (head_copy, string_copy) = self.update_values(head_copy, string_copy, move)

                    self.queue.enqueue(next_state, head_copy, string_copy, iter_count + 1)

        outputs = outputs + self.validate_symbol()
        return outputs

    def update_values(self, head, string, move):
        if move == 'r':
            head += 1
            if head == len(string):
                string = string + ['_']
        elif move == 'l':
            head -= 1
            if head == 0:
                string = ['_'] + string
        return (head, string)

    def output(self, outputs):
        if 1 in outputs:
            return 'Accepted'
        if 0 in outputs:
            return 'Rejected'
        return 'Undefined'


# Example: Automata that accepts strings that ends with 'b'
transitions = [(0, 'x', 'x', 'r', 0), (0, 'b', 'b', 's', 1)]
accepted_states = [1]
max_iterations = 50
input_strings = ['aa', 'ab', 'aaab', 'ababab', 'bba']

turing_machine = TuringMachine(transitions, accepted_states, max_iterations)
for string in input_strings:
    output = turing_machine.validate_string(list(string))
    print(string, output)


