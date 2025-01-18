import os
import pandas as pd
import matplotlib.pyplot as plt
from dataclasses import dataclass
from textwrap import wrap


@dataclass
class Comparison:
    filename: str
    data: pd.DataFrame


def load_comparison_files(
    directory: str = "./results/comparisons",
) -> list[Comparison]:
    loaded_files = []
    for filename in os.listdir(directory):
        if filename.endswith(".csv"):
            file_path = os.path.join(directory, filename)
            data = pd.read_csv(file_path)
            del data[data.columns[-1]]
            loaded_files.append(Comparison(filename.removesuffix(".csv"), data))

    return loaded_files


fname_to_param_name = {
    "activations": "Funkcja aktywacji",
    "add_connections": "Prawdopodobieństwo dodania połączenia",
    "add_node_mutations": "Prawdopodobieństwo dodania neuronu",
    "crossovers": "Prawdopodobieństwo krzyżowania",
    "inherit_disableds": "Prawdopodobieństwo odziedziczenia nieaktywnego połączenia",
    "mutation_strengths": "Siła mutacji",
    "similarities": "Parametry podobieństwa",
    "weight_mutations": "Prawdopodobieństwo mutacji wagi",
    "weight_perturbations": "Prawdopodobieństwo zaburzenia wagi",
}


def plot_sum_data(loaded_files: list[Comparison]) -> None:
    for file in loaded_files:
        filename = file.filename
        param_name = "\n".join(wrap(fname_to_param_name[filename], 20))
        data = pd.DataFrame(columns=["Nazwa talii", param_name, "Suma ocen"])

        for column in reversed(file.data.columns):
            deck, param = column.split("_", 1)
            data.loc[-1] = [
                deck,
                ", ".join(param.removesuffix("_").split("_")),
                file.data[column].sum(),
            ]
            data.index = data.index + 1
            data = data.sort_index()

        deck_names = data["Nazwa talii"].unique()
        params = data[param_name].unique()

        data = data.pivot(
            index="Nazwa talii",
            columns=param_name,
            values="Suma ocen",
        )

        data = data.loc[deck_names]
        data = data[params]

        data.plot.bar(rot=0)
        plt.ylabel("Suma ocen")
        plt.savefig(f"./plots/sum_{filename}.png", bbox_inches="tight")
        plt.close()


def plot_boxplot_data(loaded_files: list[Comparison]) -> None:
    for file in loaded_files:
        filename = file.filename
        data = pd.DataFrame(
            columns=["Nazwa talii", fname_to_param_name[filename], "Oceny"]
        )

        for column in reversed(file.data.columns):
            deck, param = column.split("_", 1)
            data.loc[-1] = [
                deck,
                ", ".join(param.removesuffix("_").split("_")),
                file.data[column],
            ]
            data.index = data.index + 1
            data = data.sort_index()

        unique_names = data["Nazwa talii"].unique()

        for name in unique_names:
            subset = data[data["Nazwa talii"] == name]
            params = subset[fname_to_param_name[filename]].unique()

            boxplot_data = [
                subset[subset[fname_to_param_name[filename]] == param]["Oceny"].values[
                    0
                ]
                for param in params
            ]
            plt.boxplot(boxplot_data, tick_labels=params, patch_artist=True)
            plt.xlabel(fname_to_param_name[filename])
            plt.ylabel("Ocena")
            plt.savefig(f"./plots/box_{name}_{filename}.png", bbox_inches="tight")
            plt.close()


def load_vs_random(
    filename: str = "./results/vs_random.csv",
) -> list[Comparison]:
    if filename.endswith(".csv"):
        data = pd.read_csv(filename)
        del data[data.columns[-1]]
        return Comparison(filename.removesuffix(".csv"), data)


def plot_vs_data(file: Comparison) -> None:
    data = pd.DataFrame(columns=["Nazwa talii", "Rodzaj gracza", "Suma ocen"])

    for column in reversed(file.data.columns):
        deck, type = column.split("_", 1)
        data.loc[-1] = [
            deck,
            ", ".join(type.removesuffix("_").split("_")),
            file.data[column].sum(),
        ]
        data.index = data.index + 1
        data = data.sort_index()

    deck_names = data["Nazwa talii"].unique()
    params = data["Rodzaj gracza"].unique()

    data = data.pivot(
        index="Nazwa talii",
        columns="Rodzaj gracza",
        values="Suma ocen",
    )

    data = data.loc[deck_names]
    data = data[params]

    data.plot.bar(rot=0)
    plt.ylabel("Suma ocen")
    plt.savefig("./plots/vs_data.png", bbox_inches="tight")
    plt.close()


if __name__ == "__main__":
    files = load_comparison_files()
    plot_sum_data(files)
    plot_boxplot_data(files)
    # plot_vs_data(load_vs_random())
