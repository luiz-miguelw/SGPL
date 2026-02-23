\# 🚀 Guia da Equipe - Projeto SGPL



\## ⚙️ Configuração

1\. `git clone` do repositório.

2\. `git flow init` (Main: main | Develop: develop).

3\. `git config gitflow.feature.finish.no-ff true` (Para manter o gráfico bonito).



\## 🛠️ Fluxo Diário

1\. Sincronize: `git checkout develop` -> `git pull origin develop`

2\. Nova tarefa: `git flow feature start nome-da-tarefa`

3\. Finalizar: `git flow feature finish nome-da-tarefa`

4\. Subir: `git push origin develop`



\## 🧪 Staging (Homologação)

Sempre que quiser atualizar a staging com o que está na develop:

`git checkout staging` -> `git merge develop` -> `git push origin staging`

