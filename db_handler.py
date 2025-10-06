# db_handler.py
import sys
import json
import psycopg2

def main():
    try:
        # 1. Read the JSON data from standard input
        input_data = json.load(sys.stdin)

        # 2. Connect to the database
        conn = psycopg2.connect(
            dbname="subset_solver_db",
            user="user1",
            password="password1",
            host="localhost"
        )
        cur = conn.cursor()

        # 3. Find or create the dataset
        cur.execute(
            "SELECT dataset_id FROM datasets WHERE numbers = %s AND target_sum = %s",
            (input_data["dataset"]["numbers"], input_data["dataset"]["target_sum"])
        )
        row = cur.fetchone()
        if row:
            dataset_id = row[0]
        else:
            cur.execute(
                "INSERT INTO datasets (numbers, target_sum) VALUES (%s, %s) RETURNING dataset_id",
                (input_data["dataset"]["numbers"], input_data["dataset"]["target_sum"])
            )
            dataset_id = cur.fetchone()[0]

        # 4. Insert the main result
        cur.execute(
            """
            INSERT INTO solve_results (dataset_id, algorithm_used, execution_time_ms, solution_found)
            VALUES (%s, %s, %s, %s) RETURNING result_id
            """,
            (
                dataset_id,
                input_data["algorithm"],
                input_data["result"]["execution_time_ms"],
                input_data["result"]["solution_found"]
            )
        )
        result_id = cur.fetchone()[0]

        # 5. Insert all found subsets
        for subset in input_data["result"]["subsets"]:
            cur.execute(
                "INSERT INTO result_subsets (result_id, subset_data) VALUES (%s, %s)",
                (result_id, subset)
            )

        # 6. Commit and close
        conn.commit()
        cur.close()
        conn.close()
        print(f"Successfully saved result via Python handler. Result ID: {result_id}")

    except Exception as e:
        print(f"Error in Python DB handler: {e}", file=sys.stderr)
        sys.exit(1)

if __name__ == "__main__":
    main()
