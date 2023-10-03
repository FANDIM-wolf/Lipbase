import random

class Object:
    def __init__(self, value, permissible_range):
        self.value = value
        self.permissible_range = permissible_range


class Table:
    def __init__(self, possible_rows, possible_columns):
        self.columns = ['column_{i}' for i in range(possible_columns)]
        self.records = []
        self.possible_rows = possible_rows
        self.possible_columns = possible_columns

    def insert_data(self, data):
        if len(self.records) < self.possible_rows and len(data) == self.possible_columns - 1:
            data.insert(0, len(self.records) + 1)  # inserting id as primary key
            self.records.append(data)
        else:
            print("Cannot insert data: Exceeds row limit or data is not correctly formatted.")

    def get_data(self, conditions):
        results = []
        for record in self.records:
            all_conditions_met = True
            for i, condition in enumerate(conditions):
                if condition != '*' and record[i] != condition:
                    all_conditions_met = False
            if all_conditions_met:
                results.append(record)
        return results

    def delete_data(self, conditions):
        new_records = []
        for record in self.records:
            all_conditions_met = False
            for i, condition in enumerate(conditions):
                if condition != '*' and record[i] == condition:
                    all_conditions_met = True
            if not all_conditions_met:
                new_records.append(record)
        self.records = new_records

    def update_data(self, conditions, new_values):
        for record in self.records:
            all_conditions_met = True
            for i, condition in enumerate(conditions):
                if condition != '*' and record[i] != condition:
                    all_conditions_met = False
            if all_conditions_met:
                for i, new_val in enumerate(new_values):
                    if new_val != '*':
                        record[i] = new_val


def create_and_fill_table(rows, cols, lower=1, upper=3):
    table = Table(rows, cols)
    for _ in range(rows):
        table.insert_data([random.randint(lower, upper) for _ in range(cols - 1)])
    return table


# Create table and fill with random values
table =Table(150 , 3)
table.insert_data([1,3])
table.update_data(["*",1,3] , ["*" ,5,5]) #we put "*" for column which we dont consider 
for record in table.records:
    print(record)