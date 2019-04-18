@app.route("/form", methods=["POST"])
def post_form():
    if not request.form['name'] or not request.form['flavor']:
        return render_template("error.html", message="You need to provide a name and at least one flavor for your sundae.")
    with open('survey.csv', 'a') as FILE:
        writer = csv.writer(FILE)
        writer.writerow((request.form['name'], request.form.getlist('flavor'), request.form.getlist('sauce'), request.form['sprinkles'], request.form['nuts'], request.form['banana'], request.form['cherry']))
    return redirect("/sheet")


@app.route("/sheet", methods=["GET"])
def get_sheet():
    with open('survey.csv', 'r') as FILE:
        reader = csv.reader(FILE)
        sundaes = list(reader)
        for sundae in sundaes:
            sundae[1] = string_array_to_string(sundae[1])
            sundae[2] = string_array_to_string(sundae[2])
    return render_template("sheet.html", sundaes=sundaes)

def string_array_to_string(arr):
    arr = ast.literal_eval(arr)
    result = ""
    for item in arr:
        if item != arr[0]:
            result += f", {item}"
        else:
            result += item
    return result
