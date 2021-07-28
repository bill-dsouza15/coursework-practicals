def PICKUP(x):
    return {
        'Name': [['PICKUP', str(x)]],
        'Precondition': [['CLEAR', str(x)], ['ONTABLE', str(x)], ['ARMEMPTY']],
        'Add': [['HOLDING', str(x)]],
        'Delete': [['ONTABLE', str(x)], ['ARMEMPTY']]
    }


def PUTDOWN(x):
    return {
        'Name': [['PUTDOWN', str(x)]],
        'Precondition': [['HOLDING', str(x)]],
        'Add': [['ONTABLE', str(x)], ['ARMEMPTY']],
        'Delete': [['HOLDING', str(x)]]
    }


def STACK(x, y):
    return {
        'Name': [['STACK', str(x), str(y)]],
        'Precondition': [['CLEAR', str(y)], ['HOLDING', str(x)]],
        'Add': [['ARMEMPTY'], ['ON', str(x), str(y)]],
        'Delete': [['CLEAR', str(y)], ['HOLDING', str(x)]]
    }


def UNSTACK(x, y):
    return {
        'Name': [['UNSTACK', str(x), str(y)]],
        'Precondition': [['ON', str(x), str(y)], ['CLEAR', str(x)], ['ARMEMPTY']],
        'Add': [['HOLDING', str(x)], ['CLEAR', str(y)]],
        'Delete': [['ON', str(x), str(y)], ['ARMEMPTY']]
    }


def print_stack(stack):
    print('\nGOAL STACK')
    for i in reversed(range(len(stack))):
        print(stack[i])


def get_achieving_action(pred, initial):
    # Get the name of predicate
    predPrefix = pred[0]
    # Get content between brackets
    pred.pop(0)
    predParam = pred

    # ONTABLE
    if predPrefix == "ONTABLE":
        return PUTDOWN(predParam[0])
    # ON
    elif predPrefix == "ON":
        return STACK(predParam[0], predParam[1])
    # CLEAR
    elif predPrefix == "CLEAR":
        check = 'ON'
        for predicate in initial:
            temp = predicate
            if check in predicate:
                if temp[2] == predParam[0]:
                    break
        predParam.insert(0, str(temp[1]))
        return UNSTACK(predParam[0], predParam[1])
    # HOLDING
    elif predPrefix == "HOLDING":
        # Check if to use PICKUP
        check = ['ONTABLE', str(predParam[0])]
        if check in initial:
            return PICKUP(predParam[0])
        # Check if to use UNSTACK
        check = 'ON'
        for predicate in initial:
            temp = predicate
            if check in predicate:
                if temp[1] == predParam[0]:
                    break
            else:
                return
        predParam.insert(1, str(temp[2]))
        return UNSTACK(predParam[0], predParam[1])


def main():
    predicates = ['ONTABLE', 'ON', 'CLEAR', 'ARMEMPTY', 'HOLDING']
    actions = ['PICKUP', 'PUTDOWN', 'STACK', 'UNSTACK']
    initial = [['ON', 'B', 'C'], ['ONTABLE', 'C'], ['ONTABLE', 'A'], ['ONTABLE', 'D'],
               ['CLEAR', 'B'], ['CLEAR', 'A'], ['CLEAR', 'D'], ['ARMEMPTY']]
    print("INITIAL")
    print(initial)
    print("\n")
    goal = [['ON', 'C', 'A'], ['ON', 'B', 'D'], ['ONTABLE', 'A'], ['ONTABLE', 'D'], ['ONTABLE', 'D'],
            ['CLEAR', 'C'], ['CLEAR', 'B'], ['ARMEMPTY']]
    print("GOAL")
    print(goal)
    print("\n")

    stack = []
    plan = []

    stack.append(goal)
    for pred in goal:
        if pred not in initial:
            stack.append(pred)

    while stack:
        print_stack(stack)
        print('\nPLAN')
        print(plan)
        print("\n")

        currTop = stack.pop()

        # Check if its a predicate
        if currTop[0] in predicates:
            # If true in current world -> continue
            if currTop in initial:
                continue
            # Else -> push action achieving it and push all preconditions onto stack
            else:
                actionDict = get_achieving_action(currTop, initial)
                # Push action to stack
                # print(actionDict)
                stack.append(actionDict['Name'][0])
                # Push all releveant predicates in precondition to stack
                for x in reversed(actionDict['Precondition']):
                    stack.append(x)
        elif currTop[0] in actions:
            if not currTop in plan:
                plan.append(currTop)
        else:
            break


main()
